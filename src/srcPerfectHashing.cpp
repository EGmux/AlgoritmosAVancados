#include "../include/includePerfectHashing.hpp"
#include <cmath>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <sys/types.h>
#include <utility>

uint32_t PerfectHashTable::h1(uint32_t k, bool isModify=false){
    if(isModify){
     m_a = !(m_isSeed) ?
                     (1 + m_rng() % (m_p - 1)) :
                     (m_isSeed = false, (1 + m_seed) % (m_p - 1));    // deal with the annoying X[0]
    m_b = m_rng() % m_p;
    }
    return (((m_a * k + m_b) % m_p) % m_m0);

    
}


PerfectHashTable::PerfectHashTable(uint32_t u, uint32_t m0, uint32_t p, RNG rng, uint32_t seed):
        m_rng(rng),
        m_u(u),
        m_m0(m0),
        m_p(p),
        m_seed(seed),
        m_isSeed(true),
        m_numKeys(0) {
    m_tableEntry.resize(m_m0);
    h1(0,true); // setup hash
};


void PerfectHashTable::Rehash() {
    auto isRehash = 2 * m_numKeys > m_tableEntry.capacity() ? true : false;
    if (isRehash) {
        m_m0 = (m_m0 << 1) + 1;          // increase the size
        auto tmpT = new FirstLvTable;    // need to allocate in the heap
        tmpT->resize(m_m0);
        h1(0,true);    // P=2^31 -1, mutates m_mH
        for (auto i : m_tableEntry) {
            if (i != nullptr) {
                for(auto j : *i){
                    auto newi = h1(j);
                    if ((*tmpT)[newi] == nullptr) {    // guarantee no segfault
                        auto fwdTmp = new std::list<uint32_t>;
                        (*tmpT)[newi] = fwdTmp;
                    }
                    (*tmpT)[newi]->push_back(j);
                }
            }
        }
        m_tableEntry.resize(m_m0);    // so we don't waste our previous capacity
        for (auto i {0}; i < m_m0; ++i) {
            if (m_tableEntry[i] != nullptr) {
                m_tableEntry[i]->clear();
            }
            m_tableEntry[i] = (*tmpT)[i];
        }
    }
}
    
std::pair<bool, uint32_t> PerfectHashTable::Get(uint32_t k) {
    auto index = h1(k);
    uint32_t acc {0};
    if(m_tableEntry[index] == nullptr){
        auto l  = new std::list<uint32_t>;
        m_tableEntry[index] = l;
    }
    for (auto i : *m_tableEntry[index]) {
        if (i == k)
            return {true, acc};
        acc++;
    }
    return {false, m_tableEntry[index]->size()};
}

std::pair<int32_t, int32_t> PerfectHashTable::Set(uint32_t k) {
    std::pair<bool, uint32_t> j;
    if (j = Get(k), !j.first) {    // means false
        Rehash();    // Check if table has too many elements
        auto i =h1(k);
        if(m_tableEntry[i] == nullptr){ // the naughtiest bug
            auto l = new std::list<uint32_t>;
            m_tableEntry[i] = l;
        }
        m_tableEntry[i]->push_back(k), m_numKeys++;
        j.second = m_tableEntry[i]->size()-1;
    }
    return {h1(k), j.second};
}