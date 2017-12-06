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
    {"L2_noninc",         0, NULL, 0},
    {"L2_evict_write",    1, NULL, 0},
    {"L3_replace_policy", 1, NULL, 0},
    {"L3_insert_policy",  1, NULL, 0},
    {"L3_noninc",         0, NULL, 0},
    {"L3_evict_write",    1, NULL, 0},
    {"L4_replace_policy", 1, NULL, 0},
    {"L4_insert_policy",  1, NULL, 0},
    {"L4_noninc",         0, NULL, 0},
    {"L4_evict_write",    1, NULL, 0},
    {"warmup_misses",     1, NULL, 0},
    {"sim_misses",        1, NULL, 0},
    {"verbose",           0, NULL, 0},
    {"L1_trace",          1, NULL, 0},
    {"L2_trace",          1, NULL, 0},
    {"L2_trace_out",      1, NULL, 0},
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
    bool L2_alloc_evict, L3_alloc_evict, L4_alloc_evict;
    bool use_L2_trace;

    int L2_evict_after_write, L3_evict_after_write, L4_evict_after_write;
    cache_stats_t *l2stats;
    
    uint64_t warmup_misses;
    uint64_t sim_misses;
    uint64_t total_misses;
    uint64_t total_insts;
    uint64_t imisscnt, dmisscnt;
    uint64_t ievictcnt, devictcnt;
    uint64_t lines;
    l1logger *l2logger;

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

    use_L2_trace = false;

    L2_alloc_evict = L3_alloc_evict = L4_alloc_evict = false;

    L2_evict_after_write = L3_evict_after_write = L4_evict_after_write = 0;

    std::string trace("");
    std::string L2_trace_out("");

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
    warmup_misses = 0;
    total_misses = total_insts = 0;
    sim_misses = -1;

    imisscnt = dmisscnt = 0;
    ievictcnt = devictcnt = 0;

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

        else if (!strcmp("L2_noninc", long_opts[optidx].name))
            L2_alloc_evict = true;
        else if (!strcmp("L3_noninc", long_opts[optidx].name))
            L3_alloc_evict = true;
        else if (!strcmp("L4_noninc", long_opts[optidx].name))
            L4_alloc_evict = true;

        else if (!strcmp("L2_evict_write", long_opts[optidx].name))
            L2_evict_after_write = atoi(optarg);
        else if (!strcmp("L3_evict_write", long_opts[optidx].name))
            L3_evict_after_write = atoi(optarg);
        else if (!strcmp("L4_evict_write", long_opts[optidx].name))
            L4_evict_after_write = atoi(optarg);

        else if (!strcmp("L2_insert_policy", long_opts[optidx].name)) {
            L2_insert_policy = std::string(optarg);
            L2_alloc_evict = true;
        } else if (!strcmp("L3_insert_policy", long_opts[optidx].name)) {
            L3_insert_policy = std::string(optarg);
            L3_alloc_evict = true;
        } else if (!strcmp("L4_insert_policy", long_opts[optidx].name)) {
            L4_insert_policy = std::string(optarg);
            L4_alloc_evict = true;
        }

        else if (!strcmp("L1_trace", long_opts[optidx].name)) {
            trace = std::string(optarg);
            use_L2_trace = false;
        } else if (!strcmp("L2_trace", long_opts[optidx].name)) {
            trace = std::string(optarg);
            use_L2_trace = true;
        }

        else if (!strcmp("L2_trace_out", long_opts[optidx].name)) {
            L2_trace_out = std::string(optarg);
            assert(!use_L2_trace);
        }

        else if (!strcmp("cores", long_opts[optidx].name))
            cores = atoi(optarg);

        else if (!strcmp("line_size", long_opts[optidx].name))
            line_size = atoi(optarg);

        else if (!strcmp("verbose", long_opts[optidx].name))
            verbose = 1;

        else if (!strcmp("warmup_misses", long_opts[optidx].name))
            warmup_misses = atol(optarg);
        else if (!strcmp("sim_misses", long_opts[optidx].name))
            sim_misses = atol(optarg);

        else
            assert(false);
    }

    if (trace.empty()) {
        printf("Please specify a trace file!\n");
        exit(-1);
    }

    l2logger = new l1logger(L2_trace_out);

    printf("Cores: %d\nLine size: %d\nVerbose: %d\nWarmup misses: %lu\nSim misses: %lu\n",
            cores, line_size, verbose, warmup_misses, sim_misses);
    printf("%s trace: %s\n", use_L2_trace?"L2":"L1", trace.c_str());
    printf("L2 trace out: %s\n", L2_trace_out.c_str());;
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

    assert(l4cache->set_inclusion_opts(L4_alloc_evict, L4_evict_after_write, L4_insert_policy));

    if (!l3cache->init(L3_assoc, line_size,
                       L3_size, l4cache, new cache_stats_t)) assert(false);

    assert(l3cache->set_inclusion_opts(L3_alloc_evict, L3_evict_after_write, L3_insert_policy));

    l2caches = new cache_t* [cores];
    l2stats = new cache_stats_t;
    for (int i = 0; i < cores; i++) {
        l2caches[i] = create_cache(L2_replace_policy);
        if (l2caches[i] == NULL) assert(false);

        if (!l2caches[i]->init(L2_assoc, line_size, L2_size, 
                    l3cache, l2stats)) assert(false);

        l2caches[i]->set_miss_logger(false, i, l2logger);

        assert(l2caches[i]->set_inclusion_opts(L2_alloc_evict, L2_evict_after_write, L2_insert_policy));
    }

    for(std::string str; std::getline(trace_buf, str); ) {
        std::stringstream rem(str);
        int _c, _i, _rdcnt, _wrcnt;
        uint64_t _a;

        if (total_misses > warmup_misses && !warmed) {
            warmed = true;
            for(int i=0; i<cores; i++) {
                l2caches[i]->get_stats()->reset();
                l2caches[i]->reset_wearout();
            }
            l3cache->get_stats()->reset();
            l4cache->get_stats()->reset();
            l3cache->reset_wearout();
            l4cache->reset_wearout();
        } else if (total_misses > sim_misses) {   
            printf("Hit miss simulation threshold.\n");
            break;
        }

        memset(&memref, 0, sizeof(ext_memref_t));

        rem.ignore(3);

        if (!strncmp(str.c_str(), "IB", 2)) {
            rem >> _c >> _i;
            l2caches[_c]->get_stats()->reg_inst(_i);
            l2caches[_c]->reg_inst(_i);
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
            memref.evict = false;
            //printf("Handling i-miss to  %16lX at core %d.\n", _a, _c);
            imisscnt++;
            total_misses++;
            l2caches[_c]->request(memref);
        } else if (!strncmp(str.c_str(), "IE", 2)) {
            rem >> _c >> _a >> _rdcnt >> _wrcnt;
            memref.ref.data.type = TRACE_TYPE_EVICT;
            memref.core = _c;
            memref.inst = true;
            memref.ref.data.size = 1;
            memref.ref.data.addr = _a;
            memref.rdcount = _rdcnt;
            memref.wrcount = _wrcnt;
            memref.evict = true;
            ievictcnt++;
            //printf("Handling i-evict to  %16lX at core %d.\n", _a, _c);
            l2caches[_c]->request(memref);
        } else if (!strncmp(str.c_str(), "DE", 2)) {
            rem >> _c >> _a >> _rdcnt >> _wrcnt;
            memref.ref.data.type = TRACE_TYPE_EVICT;
            memref.core = _c;
            memref.inst = false;
            memref.rdcount = _rdcnt;
            memref.wrcount = _wrcnt;
            memref.ref.data.size = 1;
            memref.ref.data.addr = _a;
            memref.evict = true;
            devictcnt++;
            total_misses++;
            //if (_wrcnt > 0) {
                //printf("Handling d-evict to %16lX at core %d.\n", _a, _c);
                l2caches[_c]->request(memref);
           // }
        } else if (!strncmp(str.c_str(), "DW", 2)) {
            rem >> _c >> _a;
            memref.ref.data.type = TRACE_TYPE_WRITE;
            memref.core = _c;
            memref.inst = false;
            memref.ref.data.size = 1;
            memref.ref.data.addr = _a;
            dmisscnt++;
            memref.evict = false;
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
            memref.evict = false;
            //printf("Handling d-read to  %16lX at core %d.\n", _a, _c);
            l2caches[_c]->request(memref);
        } else {
            printf("Unknown trace line: %s\n", str.c_str());
            assert(false);
        }
        lines++;
        if (lines%(1000*1000) == 0)
            printf("Handled %d million lines.\n", lines/1000/1000);
    }

    printf("Done reading trace file. %lu instructions simulated.\n", total_insts);
    printf("\tTotal %lu imiss, %lu dmiss.\n", imisscnt, dmisscnt);
    printf("\tL1I MPKI: %6.2f\n", 1000.0*imisscnt/total_insts);
    printf("\tL1D MPKI: %6.2f\n", 1000.0*dmisscnt/total_insts);
    printf("\tTotal %lu ievict, %lu devict.\n", ievictcnt, devictcnt);
    std::cout << "Cache simulation results:\n";
    //for (int i = 0; i < cores; i++) {
        //std::cout << "Core #" << i << std::endl;
	std::cout << "L2 stats:" << std::endl;
	l2caches[0]->get_stats()->print_stats("    ");
	std::cout << "L2 wearout stats:" << std::endl;
	l2caches[0]->print_wearout("    ");
    //}
    std::cout << "L3 stats:" << std::endl;
    l3cache->get_stats()->print_stats("    ");
    std::cout << "L3 wearout stats:" << std::endl;
    l3cache->print_wearout("    ");
    std::cout << "L4 stats:" << std::endl;
    l4cache->get_stats()->print_stats("    ");
    std::cout << "L4 wearout stats:" << std::endl;
    l4cache->print_wearout("    ");

    delete l2logger;

    return 0;
}
