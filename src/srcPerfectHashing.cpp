#include "../include/includePerfectHashing.hpp"
#include <cmath>
#include <cstdint>

PerfectHashTable::PerfectHashTable(uint32_t u, uint32_t m0, uint32_t p, RNG rng):m_rng(rng){
    uint32_t size = (m0%2)==0?2*std::floor((m0+1)/2)+1:2*std::floor(m0/2)+1;
    m_tableEntry->reserve(size);
    m_tableEntry->resize(size);
    m_mH = GenHash1(u, m0, p, rng);
};


MHT PerfectHashTable::GenHash1(uint32_t u, uint32_t m0, uint32_t p, RNG rng){
    uint32_t a = 1 + rng()%(p-1);
    uint32_t b = rng()%p;

    uint32_t imp(uint32_t k){
        return ((a * k + b)    % p) % m0;
    }
    return imp;
};


