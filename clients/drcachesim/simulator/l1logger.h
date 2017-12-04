#ifndef _L1LOGGER_H
#define _L1LOGGER_H

#include <string>
#include <iostream>
#include <fstream>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/bzip2.hpp>

class l1logger {
    bool active;
    std::ofstream out_stream;
    boost::iostreams::filtering_ostream output;
    char buf[1000];
public:
    l1logger(const std::string &out_file) {
        if (out_file.empty()) {
            active = false;
            return;
        }
        active = true;
        out_stream.open(out_file);

        if (strstr(out_file.c_str(), "bz2")) {
            printf("Using bz2 compression.\n");
            output.push(boost::iostreams::bzip2_compressor());
        } 
        output.push(out_stream);
    }

    ~l1logger() {
        //output.close();
    }

    void log_instr_bundle(int core, int count) {
        if (!active) return;
        output << "IB " << core << " " << count << std::endl;
    }

    void log_icache_miss(int core, uint64_t addr) {
        if (!active) return;
        output << "IM " << core << " " << addr << std::endl;
    }

    void log_icache_evict(int core, uint64_t addr, int rdcount, int wrcount) {
        if (!active) return;
        assert((addr&0x3F) == 0);
        output << "IE " << core << " " << addr << " " << rdcount << " " << wrcount << std::endl;
    }

    void log_dcache_miss(int core, uint64_t addr, bool write) {
        if (!active) return;
        if (write)
            output << "DW " << core << " " << addr << std::endl;
        else
            output << "DR " << core  << " "<< addr << std::endl;
    }

    void log_dcache_evict(int core, uint64_t addr, int rdcount, int wrcount) {
        if (!active) return;
        assert((addr&0x3F) == 0);
        output << "DE " << core << " " << addr << " " << rdcount << " " << wrcount << std::endl;
    }
};

#endif
