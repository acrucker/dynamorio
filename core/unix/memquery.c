/* *******************************************************************************
 * Copyright (c) 2010-2014 Google, Inc.  All rights reserved.
 * Copyright (c) 2011 Massachusetts Institute of Technology  All rights reserved.
 * Copyright (c) 2000-2010 VMware, Inc.  All rights reserved.
 * *******************************************************************************/

/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of VMware, Inc. nor the names of its contributors may be
 *   used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL VMWARE, INC. OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

/*
 * memquery.c - memory querying code shared across unix platforms
 */

#include "../globals.h"
#include "memquery.h"
#include "module.h"
#include <string.h>

/***************************************************************************
 * LIBRARY BOUNDS
 */

/* See memquery.h for full interface specs, which are identical to
 * memquery_library_bounds().
 */
int
memquery_library_bounds_by_iterator(const char *name, app_pc *start/*IN/OUT*/,
                                    app_pc *end/*OUT*/,
                                    char *fullpath/*OPTIONAL OUT*/, size_t path_size)
{
    int count = 0;
    bool found_library = false;
    char libname[MAXIMUM_PATH];
    const char *name_cmp = name;
    memquery_iter_t iter;
    app_pc last_base = NULL;
    app_pc last_end = NULL;
    size_t image_size = 0;
    app_pc cur_end = NULL;
    app_pc mod_start = NULL;
    ASSERT(name != NULL || start != NULL);

    /* If name is non-NULL, start can be NULL, so we have to walk the whole
     * address space even when we have syscalls for memquery (e.g., on Mac).
     * Even if start is non-NULL, it could be in the middle of the library.
     */
    memquery_iterator_start(&iter, NULL, true/*ok to alloc*/);
    libname[0] = '\0';
    while (memquery_iterator_next(&iter)) {
        LOG(GLOBAL, LOG_VMAREAS, 5, "start="PFX" end="PFX" prot=%x comment=%s\n",
            iter.vm_start, iter.vm_end, iter.prot, iter.comment);

        /* Record the base of each differently-named set of entries up until
         * we find our target, when we'll clobber libpath
         */
        if (!found_library &&
            strncmp(libname, iter.comment, BUFFER_SIZE_ELEMENTS(libname)) != 0) {
            last_base = iter.vm_start;
            /* last_end is used to know what's readable beyond last_base */
            if (TEST(MEMPROT_READ, iter.prot))
                last_end = iter.vm_end;
            else
                last_end = last_base;
            /* remember name so we can find the base of a multiply-mapped so */
            strncpy(libname, iter.comment, BUFFER_SIZE_ELEMENTS(libname));
            NULL_TERMINATE_BUFFER(libname);
        }

        if ((name_cmp != NULL &&
             (strstr(iter.comment, name_cmp) != NULL ||
              /* For Linux, include mid-library (non-.bss) anonymous mappings.
               * Our private loader
               * fills mapping holes with anonymous memory instead of a
               * MEMPROT_NONE mapping from the original file.
               * For Mac, this includes mid-library .bss.
               */
              (found_library && iter.comment[0] == '\0' && image_size != 0 &&
               iter.vm_end - mod_start < image_size))) ||
            (name == NULL && *start >= iter.vm_start && *start < iter.vm_end)) {
            if (!found_library) {
                size_t mod_readable_sz;
                char *dst = (fullpath != NULL) ? fullpath : libname;
                size_t dstsz = (fullpath != NULL) ? path_size :
                    BUFFER_SIZE_ELEMENTS(libname);
                char *slash = strrchr(iter.comment, '/');
                ASSERT_CURIOSITY(slash != NULL);
                ASSERT_CURIOSITY((slash - iter.comment) < dstsz);
                /* we keep the last '/' at end */
                ++slash;
                strncpy(dst, iter.comment, MIN(dstsz, (slash - iter.comment)));
                /* if max no null */
                dst[dstsz - 1] = '\0';
                if (name == NULL)
                    name_cmp = dst;
                found_library = true;
                /* Most library have multiple segments, and some have the
                 * ELF header repeated in a later mapping, so we can't rely
                 * on is_elf_so_header() and header walking.
                 * We use the name tracking to remember the first entry
                 * that had this name.
                 */
                if (last_base == NULL) {
                    mod_start = iter.vm_start;
                    mod_readable_sz = iter.vm_end - iter.vm_start;
                } else {
                    mod_start = last_base;
                    mod_readable_sz = last_end - last_base;
                }
                if (module_is_header(mod_start, mod_readable_sz)) {
                    app_pc mod_base, mod_end;
                    if (module_walk_program_headers(mod_start, mod_readable_sz, false,
                                                    &mod_base, &mod_end, NULL, NULL)) {
                        image_size = mod_end - mod_base;
                        LOG(GLOBAL, LOG_VMAREAS, 4, "%s: image size is "PIFX"\n",
                            __FUNCTION__, image_size);
                        ASSERT_CURIOSITY(image_size != 0);
                    } else {
                        ASSERT_NOT_REACHED();
                    }
                } else {
                    ASSERT(false && "expected elf header");
                }
            }
            count++;
            cur_end = iter.vm_end;
        } else if (found_library) {
            /* hit non-matching, we expect module segments to be adjacent */
            break;
        }
    }

    /* Xref PR 208443: .bss sections are anonymous (no file name listed in
     * maps file), but not every library has one.  We have to parse the ELF
     * header to know since we can't assume that a subsequent anonymous
     * region is .bss. */
    if (image_size != 0 && cur_end - mod_start < image_size) {
        /* Found a .bss section. Check current mapping (note might only be
         * part of the mapping (due to os region merging? FIXME investigate). */
        ASSERT_CURIOSITY(iter.vm_start == cur_end /* no gaps, FIXME might there be
                                                   * a gap if the file has large
                                                   * alignment and no data section?
                                                   * curiosity for now*/);
        ASSERT_CURIOSITY(iter.inode == 0); /* .bss is anonymous */
        ASSERT_CURIOSITY(iter.vm_end - mod_start >= image_size);/* should be big enough */
        count++;
        cur_end = mod_start + image_size;
    } else {
        /* Shouldn't have more mapped then the size of the module, unless it's a
         * second adjacent separate map of the same file.  Curiosity for now. */
        ASSERT_CURIOSITY(image_size == 0 || cur_end - mod_start == image_size);
    }
    memquery_iterator_stop(&iter);

    if (start != NULL)
        *start = mod_start;
    if (end != NULL)
        *end = cur_end;
    return count;
}
