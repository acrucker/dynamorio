/* **********************************************************
 * Copyright (c) 2015-2017 Google, Inc.  All rights reserved.
 * **********************************************************/

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
 * * Neither the name of Google, Inc. nor the names of its contributors may be
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

#include "caching_device.h"
#include "caching_device_block.h"
#include "caching_device_stats.h"
#include "prefetcher.h"
#include "../common/utils.h"
#include "../common/trace_entry.h"
#include "l1logger.h"
#include <assert.h>
#include <iostream>
#include <iomanip>

caching_device_t::caching_device_t() :
    blocks(NULL), stats(NULL), logger(NULL), prefetcher(NULL)
{
    /* Empty. */
}

caching_device_t::~caching_device_t()
{
    if (blocks == NULL)
        return;
    for (int i = 0; i < num_blocks; i++)
        delete blocks[i];
    delete [] blocks;
}

bool
caching_device_t::init(int associativity_, int block_size_, int num_blocks_,
                       caching_device_t *parent_, caching_device_stats_t *stats_,
                       prefetcher_t *prefetcher_)
{
    if (!IS_POWER_OF_2(associativity_) ||
        !IS_POWER_OF_2(block_size_) ||
        !IS_POWER_OF_2(num_blocks_) ||
        // Assuming caching device block size is at least 4 bytes
        block_size_ < 4)
        return false;
    if (stats_ == NULL)
        return false; // A stats must be provided for perf: avoid conditional code
    else if (!*stats_)
        return false;
    associativity = associativity_;
    block_size = block_size_;
    num_blocks = num_blocks_;
    blocks_per_set = num_blocks / associativity;
    assoc_bits = compute_log2(associativity);
    block_size_bits = compute_log2(block_size);
    recent_instructions = 0;
    blocks_per_set_mask = blocks_per_set - 1;
    if (assoc_bits == -1 || block_size_bits == -1 || !IS_POWER_OF_2(blocks_per_set))
        return false;
    parent = parent_;
    stats = stats_;
    prefetcher = prefetcher_;

    evict_after_n_writes = 0;
    alloc_on_evict = false;
    inclusion = new include_all();

    std::cout << "Creating a cache with " << block_size_*num_blocks_ << " total bytes.\n";
    blocks = new caching_device_block_t* [num_blocks];
    init_blocks();

    last_tag = TAG_INVALID; // sentinel
    return true;
}

void
caching_device_t::request(const memref_t &memref_in)
{
    ext_memref_t gen_memref;
    gen_memref.ref     = memref_in;
    gen_memref.rdcount = 0;
    gen_memref.wrcount = 0;
    gen_memref.core    = 0;
    gen_memref.inst    = false;
    
    caching_device_t::request(gen_memref);
}

bool
caching_device_t::set_inclusion_opts(bool _alloc_on_evict, 
        int _evict_after_n_writes,
        std::string include_policy) {
    if (_evict_after_n_writes < 0)
        return false;

    if(!strcmp(include_policy.c_str(), "all")) {
        inclusion = new include_all();
    } else if (!strcmp(include_policy.c_str(), "none")) {
        inclusion = new include_none();
    } else {
        return false;
    }

    alloc_on_evict = _alloc_on_evict;
    evict_after_n_writes = _evict_after_n_writes;

    return true;
}

void
caching_device_t::evict(int block_idx, int way) {
    caching_device_block_t &b = get_caching_device_block(block_idx, way);
    if (b.dirty) {
        memref_t wb;
        wb.data.type = TRACE_TYPE_WRITE;
        wb.data.pid = 0;
        wb.data.tid = 0;
        wb.data.addr = b.tag << block_size_bits;
        wb.data.size = block_size;
        wb.data.pc = 0;
        if (parent) 
            parent->request(wb);
    }
    inclusion->update_evict(b.tag<<block_size_bits, b.rdcount, b.wrcount);
    if (b.tag != TAG_INVALID) {
        if (logger) {
            uintptr_t addr = b.tag << block_size_bits;
            if (isicache) {
                logger->log_icache_evict(core, addr, b.rdcount, b.wrcount);
            } else {
                logger->log_dcache_evict(core, addr, b.rdcount, b.wrcount);
            }
        }
        stats->evict(!b.dirty);
    }
}

void
caching_device_t::request(const ext_memref_t &ext_memref_in)
{
    // Unfortunately we need to make a copy for our loop so we can pass
    // the right data struct to the parent and stats collectors.
    memref_t memref;
    const memref_t &memref_in = ext_memref_in.ref;

    bool is_evict = ext_memref_in.rdcount + ext_memref_in.wrcount > 0;

    // Update counters with subordinate stats

    // If allocation is being done on misses and this is a clean evict, disregard
    if (!alloc_on_evict && ext_memref_in.wrcount == 0)
        return;

    // We support larger sizes to improve the IPC perf.
    // This means that one memref could touch multiple blocks.
    // We treat each block separately for statistics purposes.
    addr_t final_addr = memref_in.data.addr + memref_in.data.size - 1/*avoid overflow*/;
    addr_t final_tag = compute_tag(final_addr);
    addr_t tag = compute_tag(memref_in.data.addr);

    assert(!(isicache && type_is_write(memref_in.data.type)));

    // Optimization: check last tag if single-block and read
    if (tag == final_tag && tag == last_tag && !is_evict && !type_is_write(memref_in.data.type)) {
        // Make sure last_tag is properly in sync.
        assert(tag != TAG_INVALID &&
               tag == get_caching_device_block(last_block_idx, last_way).tag);
        stats->access(memref_in, true/*hit*/);
        get_caching_device_block(last_block_idx, last_way).rdcount++;
        if (parent != NULL)
            parent->stats->child_access(memref_in, true);
        access_update(last_block_idx, last_way);
        return;
    }

    // Invalidate last tag when handling writes
    last_tag = TAG_INVALID;

    memref = memref_in;
    for (; tag <= final_tag; ++tag) {
        int way;
        int block_idx = compute_block_idx(tag);
        bool missed = false;

        assert(!(isicache && type_is_write(memref.data.type)));

        if (tag + 1 <= final_tag)
            memref.data.size = ((tag + 1) << block_size_bits) - memref.data.addr;

        for (way = 0; way < associativity; ++way) {
            if (get_caching_device_block(block_idx, way).tag == tag) {
                if (type_is_write(memref.data.type)) {
                    write_update(block_idx, way);
                    get_caching_device_block(block_idx, way).dirty = true;
                    get_caching_device_block(block_idx, way).wrcount++;
                    if (evict_after_n_writes && 
                        get_caching_device_block(block_idx, way).wrcount 
                        > evict_after_n_writes) {
                        evict(block_idx, way);
                        break;
                    }
                } else {
                    get_caching_device_block(block_idx, way).rdcount++;
                }
                stats->access(memref, true/*hit*/);
                if (parent != NULL)
                    parent->stats->child_access(memref, true);
                break;
            }
        }

        if (way == associativity) {
            stats->access(memref, false/*miss*/);
            missed = true;
            // If no parent we assume we get the data from main memory
            if (parent != NULL) {
                parent->stats->child_access(memref, false);
                parent->request(memref);
            }

            // Don't allocate on miss if we're allocating on evictions from below
            if (alloc_on_evict && !is_evict)
                continue;

            // If the insertion policy tells us not to allocate, don't
            if (alloc_on_evict && !inclusion->should_alloc(tag << block_size_bits,
                        ext_memref_in.rdcount, ext_memref_in.wrcount, 
                        ext_memref_in.inst))
                continue;
                        
            // FIXME i#1726: coherence policy

            way = replace_which_way(block_idx);
            evict(block_idx, way);

            if (logger && isicache) {
                logger->log_instr_bundle(core, recent_instructions);
                recent_instructions = 0;
            }
            if (logger) {
                uintptr_t addr = tag << block_size_bits;
                if (isicache) {
                    logger->log_icache_miss(core, addr);
                } else {
                    logger->log_dcache_miss(core, addr, type_is_write(memref.data.type));
                }
            }
            caching_device_block_t &b = get_caching_device_block(block_idx, way);
            b.tag = tag;
            b.dirty = false;
            b.rdcount = b.wrcount = 0;
            write_update(block_idx, way);
        }

        access_update(block_idx, way);

        // Issue a hardware prefetch, if any, before we remember the last tag,
        // so we remember this line and not the prefetched line.
        if (missed && !type_is_prefetch(memref.data.type) && prefetcher != nullptr)
            prefetcher->prefetch(this, memref);

        if (tag + 1 <= final_tag) {
            addr_t next_addr = (tag + 1) << block_size_bits;
            memref.data.addr = next_addr;
            memref.data.size = final_addr - next_addr + 1/*undo the -1*/;
        }

        // Optimization: remember last tag
        last_tag = tag;
        last_way = way;
        last_block_idx = block_idx;
    }
}

void
caching_device_t::write_update(int block_idx, int way)
{
    get_caching_device_block(block_idx, way).wearout_counter++;
}

void
caching_device_t::print_wearout(std::string prefix)
{
    int_least64_t max_wearout = 0;
    int_least64_t total_wearout = 0;
    for (int i=0; i<num_blocks; i++) {
        if(blocks[i]->wearout_counter > max_wearout)
            max_wearout = blocks[i]->wearout_counter;

        total_wearout += blocks[i]->wearout_counter;
    }

    std::cout << prefix << std::setw(18) << std::left << "Maximum wear:" <<
        std::setw(20) << std::right << max_wearout << std::endl;
    std::cout << prefix << std::setw(18) << std::left << "Mean wear:" <<
        std::setw(20) << std::fixed << std::setprecision(2) << std::right <<
        ((float)total_wearout/num_blocks) << std::endl;
    std::cout << prefix << std::setw(18) << std::left << "Total updates:" <<
        std::setw(20) << std::right << total_wearout << std::endl;
}

void
caching_device_t::access_update(int block_idx, int way)
{
    // We just inc the counter for LFU.  We live with any blip on overflow.
    get_caching_device_block(block_idx, way).counter++;
}

int
caching_device_t::replace_which_way(int block_idx)
{
    // The base caching device class only implements LFU.
    // A subclass can override this and access_update() to implement
    // some other scheme.
    int min_counter = 0; /* avoid "may be used uninitialized" with GCC 4.4.7 */
    int min_way = 0;
    for (int way = 0; way < associativity; ++way) {
        if (get_caching_device_block(block_idx, way).tag == TAG_INVALID) {
            min_way = way;
            break;
        }
        if (way == 0 || get_caching_device_block(block_idx, way).counter < min_counter) {
            min_counter = get_caching_device_block(block_idx, way).counter;
            min_way = way;
        }
    }
    // Clear the counter for LFU.
    get_caching_device_block(block_idx, min_way).counter = 0;
    return min_way;
}
