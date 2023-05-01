#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <cstdint>
#include <vector>


struct vanEmdeBoas{
    uint32_t high(uint32_t x);
    uint32_t low(uint32_t x);
    uint32_t index(uint32_t h, uint32_t l);

    uint32_t succ(uint32_t x);
    uint32_t insert(uint32_t x);
    uint32_t remove(uint32_t x);

};


#endif //SKIP_LIST_H