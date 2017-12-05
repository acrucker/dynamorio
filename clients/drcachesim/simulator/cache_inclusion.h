#ifndef _CACHE_INCLUSION_H
#define _CACHE_INCLUSION_H

#include <cstdlib>
#include <vector>

using std::vector;

struct cache_inclusion_t {
    virtual void update_evict(int addr, int rdcount, int wrcount) = 0;
    virtual bool should_alloc(int addr, int rdcount, int wrcount, bool isinst) = 0;
};

struct include_all : public cache_inclusion_t {
    void update_evict(int addr, int rdcount, int wrcount) {}
    bool should_alloc(int addr, int rdcount, int wrcount, bool isinst) {return true;}
};

struct include_none : public cache_inclusion_t {
    void update_evict(int addr, int rdcount, int wrcount) {}
    bool should_alloc(int addr, int rdcount, int wrcount, bool isinst) {return false;}
};

struct include_write_threshold : public cache_inclusion_t {
    int threshold;
    include_write_threshold(int _threshold) : threshold(_threshold) {}
    void update_evict(int addr, int rdcount, int wrcount) {}
    bool should_alloc(int addr, int rdcount, int wrcount, bool isinst) {return wrcount <= threshold;}
};

struct include_random : public cache_inclusion_t {
    int threshold;
    include_random(int _threshold) : threshold(_threshold) {}
    void update_evict(int addr, int rdcount, int wrcount) {}
    bool should_alloc(int addr, int rdcount, int wrcount, bool isinst) {return std::rand() % 100 < threshold;}
};

struct include_bloom : public cache_inclusion_t {
    int size;
    vector<bool> filt;
    include_bloom(int _size) : size(_size) {
        filt.resize(size);
    }
    void update_evict(int addr, int rdcount, int wrcount) {
        if (wrcount > 0) {
            int hash = (((addr/size)^addr)>>6)%size;
            filt[hash] = true;
        }
    }
    bool should_alloc(int addr, int rdcount, int wrcount, bool isinst) {
        int hash = ((unsigned int)(((addr/size)^addr)>>6))%size;
        return !filt[hash];
    }
};


#endif
