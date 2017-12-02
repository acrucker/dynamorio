#include <assert.h>
#include <iostream>
#include <sstream>
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/bzip2.hpp>

//#include "cache_simulator.h"
#include "cache.h"
#include "cache_stats.h"
#include "cache_lru.h"
#include "cache_fifo.h"

#define REPLACE_POLICY_NON_SPECIFIED            ""
#define REPLACE_POLICY_LRU                      "LRU"
#define REPLACE_POLICY_LFU                      "LFU"
#define REPLACE_POLICY_FIFO                     "FIFO"
#define PREFETCH_POLICY_NEXTLINE                "nextline"
#define PREFETCH_POLICY_NONE                    "none"

static struct option long_opts[] =
{
    {"L2_size",           1, NULL, 0},
    {"L2_assoc",          1, NULL, 0},
    {"L3_size",           1, NULL, 0},
    {"L3_assoc",          1, NULL, 0},
    {"L4_size",           1, NULL, 0},
    {"L4_assoc",          1, NULL, 0},
    {"cores",             1, NULL, 0},
    {"line_size",         1, NULL, 0},
    {"L2_replace_policy", 1, NULL, 0},
    {"L2_insert_policy",  1, NULL, 0},
    {"L3_replace_policy", 1, NULL, 0},
    {"L3_insert_policy",  1, NULL, 0},
    {"L4_replace_policy", 1, NULL, 0},
    {"L4_insert_policy",  1, NULL, 0},
    {"warmup_insts",      1, NULL, 0},
    {"sim_insts",         1, NULL, 0},
    {"verbose",           0, NULL, 0},
    {"trace",             1, NULL, 0},
    {NULL,                0, NULL, 0}
};

cache_t* create_cache(std::string policy)
{
    if (policy == REPLACE_POLICY_NON_SPECIFIED || // default LRU
        policy == REPLACE_POLICY_LRU) // set to LRU
        return new cache_lru_t;
    if (policy == REPLACE_POLICY_LFU) // set to LFU
        return new cache_t;
    if (policy == REPLACE_POLICY_FIFO) // set to FIFO
        return new cache_fifo_t;

    // undefined replacement policy
    ERRMSG("Usage error: undefined replacement policy. "
           "Please choose " REPLACE_POLICY_LRU" or " REPLACE_POLICY_LFU".\n");
    return NULL;
}

int main(int argc, char **argv) {
    int optidx;
    int L2_size, L2_assoc;
    int L3_size, L3_assoc;
    int L4_size, L4_assoc;
    int cores;
    int line_size;
    int verbose;
    bool use_bz2;
    bool warmed;

    uint64_t warmup_insts;
    uint64_t sim_insts;
    uint64_t total_insts;
    uint64_t imisscnt, dmisscnt;
    uint64_t lines;

    cache_t **l2caches;

    cache_t *l3cache;
    cache_t *l4cache;

    ext_memref_t memref;

    std::string L2_replace_policy("LRU");
    std::string L3_replace_policy("LRU");
    std::string L4_replace_policy("LRU");

    std::string L2_insert_policy("all");
    std::string L3_insert_policy("all");
    std::string L4_insert_policy("all");

    std::string trace("");

    std::ifstream trace_file;
    boost::iostreams::filtering_istream trace_buf;

    L2_size = 256*1024;
    L3_size = 16*1024*1024;
    L4_size = 1024*1024*1024;
    L2_assoc = L3_assoc = L4_assoc = 16;

    cores = 4;
    line_size = 64;
    verbose = 0;

    warmed = false;
    warmup_insts = 0;
    total_insts = 0;
    sim_insts = -1;

    imisscnt = dmisscnt = 0;

    lines = 0;

    while (!getopt_long_only(argc, argv, "", long_opts, &optidx)) {
        if (!strcmp("L2_size", long_opts[optidx].name))
            L2_size = atoi(optarg);
        else if (!strcmp("L3_size", long_opts[optidx].name))
            L3_size = atoi(optarg);
        else if (!strcmp("L4_size", long_opts[optidx].name))
            L4_size = atoi(optarg);

        else if (!strcmp("L2_assoc", long_opts[optidx].name))
            L2_assoc = atoi(optarg);
        else if (!strcmp("L3_assoc", long_opts[optidx].name))
            L3_assoc = atoi(optarg);
        else if (!strcmp("L4_assoc", long_opts[optidx].name))
            L4_assoc = atoi(optarg);

        else if (!strcmp("L2_replace_policy", long_opts[optidx].name))
            L2_replace_policy = std::string(optarg);
        else if (!strcmp("L3_replace_policy", long_opts[optidx].name))
            L3_replace_policy = std::string(optarg);
        else if (!strcmp("L4_replace_policy", long_opts[optidx].name))
            L4_replace_policy = std::string(optarg);

        else if (!strcmp("L2_insert_policy", long_opts[optidx].name))
            L2_insert_policy = std::string(optarg);
        else if (!strcmp("L3_insert_policy", long_opts[optidx].name))
            L3_insert_policy = std::string(optarg);
        else if (!strcmp("L4_insert_policy", long_opts[optidx].name))
            L4_insert_policy = std::string(optarg);

        else if (!strcmp("trace", long_opts[optidx].name))
            trace = std::string(optarg);

        else if (!strcmp("cores", long_opts[optidx].name))
            cores = atoi(optarg);

        else if (!strcmp("line_size", long_opts[optidx].name))
            line_size = atoi(optarg);

        else if (!strcmp("verbose", long_opts[optidx].name))
            verbose = 1;

        else if (!strcmp("warmup_insts", long_opts[optidx].name))
            warmup_insts = atol(optarg);
        else if (!strcmp("sim_insts", long_opts[optidx].name))
            sim_insts = atol(optarg);

        else
            assert(false);
    }

    if (trace.empty()) {
        printf("Please specify a trace file!\n");
        exit(-1);
    }

    printf("Cores: %d\nLine size: %d\nVerbose: %d\nWarmup insts: %lu\nSim insts: %lu\n",
            cores, line_size, verbose, warmup_insts, sim_insts);
    printf("Trace: %s\n", trace.c_str());
    printf("L2 caches:\n\tSize: %d\n\tAssoc: %d\n\tReplace: %s\n\tInsert: %s\n",
            L2_size, L2_assoc, L2_replace_policy.c_str(), L2_insert_policy.c_str());
    printf("L3 cache:\n\tSize: %d\n\tAssoc: %d\n\tReplace: %s\n\tInsert: %s\n",
            L3_size, L3_assoc, L3_replace_policy.c_str(), L3_insert_policy.c_str());
    printf("L4 cache:\n\tSize: %d\n\tAssoc: %d\n\tReplace: %s\n\tInsert: %s\n",
            L4_size, L4_assoc, L4_replace_policy.c_str(), L4_insert_policy.c_str());

    trace_file = std::ifstream(trace, std::ios_base::in | std::ios_base::binary);

    if (strstr(trace.c_str(), "bz2")) {
        printf("Using bz2 decompression.\n");
        trace_buf.push(boost::iostreams::bzip2_decompressor());
    } 
    trace_buf.push(trace_file);

    l4cache = create_cache(L4_replace_policy);
    if (l4cache == NULL) assert(false);

    l3cache = create_cache(L3_replace_policy);
    if (l3cache == NULL) assert(false);

    /*if (data_prefetcher != PREFETCH_POLICY_NEXTLINE &&
        data_prefetcher != PREFETCH_POLICY_NONE) assert(false);*/

    if (!l4cache->init(L4_assoc, line_size, 
                L4_size, NULL, new cache_stats_t)) assert(false);

    //assert(l4cache->set_inclusion(L4_inclusion_policy));

    if (!l3cache->init(L3_assoc, line_size,
                       L3_size, l4cache, new cache_stats_t)) assert(false);

    //assert(l3cache->set_inclusion(L3_inclusion_policy));

    l2caches = new cache_t* [cores];
    for (int i = 0; i < cores; i++) {
        l2caches[i] = create_cache(L2_replace_policy);
        if (l2caches[i] == NULL) assert(false);

        if (!l2caches[i]->init(L2_assoc, line_size, L2_size, 
                    l3cache, new cache_stats_t)) assert(false);

        //assert(l2caches[i]->set_inclusion(L2_inclusion_policy));
    }

    for(std::string str; std::getline(trace_buf, str); ) {
        std::stringstream rem(str);
        int _c, _i, _rdcnt, _wrcnt;
        uint64_t _a;

        if (total_insts > warmup_insts && !warmed) {
            warmed = true;
            for(int i=0; i<cores; i++)
                l2caches[i]->get_stats()->reset();
            l3cache->get_stats()->reset();
            l4cache->get_stats()->reset();
        }

        memset(&memref, 0, sizeof(ext_memref_t));

        rem.ignore(3);

        if (!strncmp(str.c_str(), "IB", 2)) {
            rem >> _c >> _i;
            l2caches[_c]->get_stats()->reg_inst(_i);
            l3cache->get_stats()->reg_inst(_i);
            l4cache->get_stats()->reg_inst(_i);
            total_insts += _i;
            //printf("Registered %d insts at core %d.\n", _i, _c);
        } else if (!strncmp(str.c_str(), "IM", 2)) {
            rem >> _c >> _a;
            memref.ref.data.type = TRACE_TYPE_READ;
            memref.core = _c;
            memref.inst = true;
            memref.ref.data.size = 1;
            memref.ref.data.addr = _a;
            //printf("Handling i-miss to  %16lX at core %d.\n", _a, _c);
            imisscnt++;
            l2caches[_c]->request(memref);
        } else if (!strncmp(str.c_str(), "IE", 2)) {
            rem >> _c >> _a >> _rdcnt >> _wrcnt;
        } else if (!strncmp(str.c_str(), "DE", 2)) {
            rem >> _c >> _a >> _rdcnt >> _wrcnt;
            memref.ref.data.type = TRACE_TYPE_WRITE;
            memref.core = _c;
            memref.inst = false;
            memref.rdcount = _rdcnt;
            memref.wrcount = _wrcnt;
            memref.ref.data.size = 1;
            memref.ref.data.addr = _a;
            if (_wrcnt > 0) {
                //printf("Handling d-evict to %16lX at core %d.\n", _a, _c);
                l2caches[_c]->request(memref);
            }
        } else if (!strncmp(str.c_str(), "DW", 2)) {
            rem >> _c >> _a;
            memref.ref.data.type = TRACE_TYPE_WRITE;
            memref.core = _c;
            memref.inst = false;
            memref.ref.data.size = 1;
            memref.ref.data.addr = _a;
            dmisscnt++;
            //printf("Handling d-write to %16lX at core %d.\n", _a, _c);
            l2caches[_c]->request(memref);
        } else if (!strncmp(str.c_str(), "DR", 2)) {
            rem >> _c >> _a;
            memref.ref.data.type = TRACE_TYPE_READ;
            memref.core = _c;
            memref.inst = false;
            memref.ref.data.size = 1;
            memref.ref.data.addr = _a;
            dmisscnt++;
            //printf("Handling d-read to  %16lX at core %d.\n", _a, _c);
            l2caches[_c]->request(memref);
        } else {
            printf("Unknown trace line: %s\n", str.c_str());
            assert(false);
        }
        lines++;
        if (lines%50000 == 0)
            printf("Handled %llu lines.\n", lines);
    }

    printf("Done reading trace file. %d instructions simulated.\n", total_insts);
    printf("\tTotal %d imiss, %d dmiss.\n", imisscnt, dmisscnt);
    std::cerr << "Cache simulation results:\n";
    for (int i = 0; i < cores; i++) {
        std::cerr << "Core #" << i << std::endl;
        std::cerr << "  L2 stats:" << std::endl;
        l2caches[i]->get_stats()->print_stats("    ");
        std::cerr << "  L2 wearout stats:" << std::endl;
        l2caches[i]->print_wearout("    ");
    }
    std::cerr << "L3 stats:" << std::endl;
    l3cache->get_stats()->print_stats("    ");
    std::cerr << "L3 wearout stats:" << std::endl;
    l3cache->print_wearout("    ");
    std::cerr << "L4 stats:" << std::endl;
    l4cache->get_stats()->print_stats("    ");
    std::cerr << "L4 wearout stats:" << std::endl;
    l4cache->print_wearout("    ");

    return 0;
}
