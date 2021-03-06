/* **********************************************************
 * Copyright (c) 2015-2016 Google, Inc.  All rights reserved.
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

/* This is the data format that the simulator and analysis tools take as input. */

#ifndef _MEMREF_H_
#define _MEMREF_H_ 1

#include <stdint.h>
#include <stddef.h> // for size_t
#include "trace_entry.h"

// On some platforms, like MacOS, a thread id is 64 bits.
// We just make both 64 bits to cover all our bases.
typedef int_least64_t memref_pid_t;
typedef int_least64_t memref_tid_t;

// Each trace entry is one of the following.
// Although the pc of each data reference is provided, the trace also guarantees that
// an instruction entry immediately precedes the data references that it is
// responsible for, with no intervening trace entries.

struct _memref_data_t {
    // TRACE_TYPE_READ, TRACE_TYPE_WRITE, and TRACE_TYPE_PREFETCH*:
    // data references.
    trace_type_t type;
    memref_pid_t pid;
    memref_tid_t tid;
    addr_t addr;
    size_t size;
    addr_t pc;
};

struct _memref_instr_t {
    // TRACE_TYPE_INSTR_* (minus BUNDLE): instruction fetch.
    trace_type_t type;
    memref_pid_t pid;
    memref_tid_t tid;
    addr_t addr;
    size_t size;
};

struct _memref_flush_t {
    // TRACE_TYPE_INSTR_FLUSH, TRACE_TYPE_DATA_FLUSH: explicit cache flush.
    trace_type_t type;
    memref_pid_t pid;
    memref_tid_t tid;
    addr_t addr;
    size_t size;
    addr_t pc;
};

struct _memref_thread_exit_t {
    // TRACE_TYPE_THREAD_EXIT.
    trace_type_t type;
    memref_pid_t pid;
    memref_tid_t tid;
};

typedef union _memref_t {
    // The C standard allows us to reference the type field of any of these, and the
    // addr and size fields of data, instr, or flush generically if known to be one
    // of those types, due to the shared fields in our union of structs.
    struct _memref_data_t data;
    struct _memref_instr_t instr;
    struct _memref_flush_t flush;
    struct _memref_thread_exit_t exit;
} memref_t;

typedef struct _ext_memref_t {
    memref_t ref;
    int rdcount;
    int wrcount;
    int core;
    bool inst;
    bool evict;
} ext_memref_t;

#endif /* _MEMREF_H_ */
