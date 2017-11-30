#ifndef _L1LOGGER_H
#define _L1LOGGER_H

#include <string>
#include <iostream>
#include <fstream>

class l1logger {
    bool active;
    std::ofstream output;
public:
    l1logger(const std::string &out_file) {
        if (out_file.empty()) {
            active = false;
            return;
        }
        active = true;
        output.open(out_file);
    }

    ~l1logger() {
        output.close();
    }

    void log_instr_bundle(int core, int count) {
        if (!active) return;
        output << "IB " << core << " " << count << std::endl;
    }

    void log_icache_miss(int core, uintptr_t addr) {
        if (!active) return;
        output << "IM " << core << " " << addr << std::endl;
    }

    void log_icache_evict(int core, uintptr_t addr, int rdcount, int wrcount) {
        if (!active) return;
        output << "IE " << core << " " << addr << " " << rdcount << " " << wrcount << std::endl;
    }

    void log_dcache_miss(int core, uintptr_t addr, bool write) {
        if (!active) return;
        if (write)
            output << "DW " << core << " " << addr << std::endl;
        else
            output << "DR " << core  << " "<< addr << std::endl;
    }

    void log_dcache_evict(int core, uintptr_t addr, int rdcount, int wrcount) {
        if (!active) return;
        output << "DE " << core << " " << addr << " " << rdcount << " " << wrcount << std::endl;
    }
};

#endif
