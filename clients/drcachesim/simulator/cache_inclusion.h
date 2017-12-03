#ifndef _CACHE_INCLUSION_H
#define _CACHE_INCLUSION_H

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

#endif
