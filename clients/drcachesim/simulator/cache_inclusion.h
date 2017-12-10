#ifndef _CACHE_INCLUSION_H
#define _CACHE_INCLUSION_H

#include <cstdlib>
#include <vector>

using std::vector;

struct cache_inclusion_t {
    virtual void update_evict(uint64_t addr) = 0;
    virtual bool should_alloc(uint64_t addr, int rdcount, int wrcount, bool isinst) = 0;
};

struct include_all : public cache_inclusion_t {
    void update_evict(uint64_t addr) {}
    bool should_alloc(uint64_t addr, int rdcount, int wrcount, bool isinst) {return true;}
};

struct include_none : public cache_inclusion_t {
    void update_evict(uint64_t addr) {}
    bool should_alloc(uint64_t addr, int rdcount, int wrcount, bool isinst) {return false;}
};

struct include_inst : public cache_inclusion_t {
    void update_evict(uint64_t addr) {}
    bool should_alloc(uint64_t addr, int rdcount, int wrcount, bool isinst) {return isinst;}
};

struct include_read_threshold : public cache_inclusion_t {
    int threshold;
    include_read_threshold(int _threshold) : threshold(_threshold) {}
    void update_evict(uint64_t addr) {}
    bool should_alloc(uint64_t addr, int rdcount, int wrcount, bool isinst) {return rdcount >= threshold;}
};

struct include_write_threshold : public cache_inclusion_t {
    int threshold;
    include_write_threshold(int _threshold) : threshold(_threshold) {}
    void update_evict(uint64_t addr) {}
    bool should_alloc(uint64_t addr, int rdcount, int wrcount, bool isinst) {return wrcount <= threshold;}
};

struct include_random : public cache_inclusion_t {
    int threshold;
    include_random(int _threshold) : threshold(_threshold) {}
    void update_evict(uint64_t addr) {}
    bool should_alloc(uint64_t addr, int rdcount, int wrcount, bool isinst) {return std::rand() % 100 < threshold;}
};

struct include_bloom : public cache_inclusion_t {
    int size;
    int threshold;
    bool clean;
    int hashcount;
    vector<bool> filt;
    include_bloom(int _size, int _hashcount, int _threshold, bool _clean) :
		size(_size), hashcount(_hashcount), threshold(_threshold), clean(_clean) {
        filt.resize(size);
    }
    void update_evict(uint64_t addr) {
        for (int i=0; i<hashcount; i++) {
            unsigned int hash = fnv_hash(i, addr) % size;
            filt[hash] = true;
        }
    }
    bool should_alloc(uint64_t addr, int rdcount, int wrcount, bool isinst) {
        if (std::rand() % 100 > threshold)
            return false;
        if (clean && wrcount)
            return false;
        bool present = true;
        for (int i=0; i<hashcount; i++) {
            unsigned int hash = fnv_hash(i, addr) % size;
            present &= filt[hash];
        }
        return !present;
    }
    uint64_t fnv_hash(uint64_t ind, uint64_t addr) {
        addr >>= 6;
        uint64_t hash = 0xcbf29ce484222325ULL;
        hash ^= ind;
        hash *= 1099511628211ULL;
        for  (int i=0; i<8; i++) {
            hash ^= (addr>>(8*i))&0xFF;
            hash *= 1099511628211ULL;
        }
        return hash;
    }
};


#endif
