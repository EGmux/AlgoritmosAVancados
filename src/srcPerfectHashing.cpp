#include "../include/includePerfectHashing.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <sys/types.h>
#include <utility>
#include <memory>

PerfectHashTable::PerfectHashTable(uint32_t u, uint32_t m0, uint32_t p, RNG rng):m_rng(rng),m_u(u),m_m0(m0),m_p(p){
    m_tableEntry->reserve(m_m0);
    m_tableEntry->resize(m_m0);
    GenHash1();
};

void PerfectHashTable::GenHash1(){
    uint32_t a = 1 + m_rng()%(m_p-1);
    uint32_t b = m_rng()%m_p;
    auto u = m_u;
    auto p = m_p;
    auto m0 = m_m0;

    // read this https://stackoverflow.com/questions/7852101/c-lambda-with-captures-as-a-function-pointer
    // Zhang's answer
    static auto impl = [a, b, u, m0, p](uint32_t k){return (((a*k + b)%p)%m0);};
    m_mH = [](uint32_t k){return impl(k);};
};

void PerfectHashTable::Rehash(){
    auto isRehash = 2*m_numKeys>m_tableEntry->size()?true:false;
    if(isRehash){
        m_m0 = (m_m0 << 2) + 1; // increase the size
        auto tmpT = new FirstLvTable;  //need to allocate in the heap
        tmpT->resize(m_m0);
        GenHash1(); // P=2^31 -1, mutates m_mH
        for(auto &i: *m_tableEntry){ // acces the indexes of the hashtable
            for(auto &j : i){ // access the entries in the linked list
                auto newi = m_mH(j);
                (*tmpT)[newi].insert_after((*tmpT)[newi].begin(),j);
            }
        }
        m_tableEntry->clear();
        m_tableEntry->resize(m_m0);
        for(auto i{0}; i < m_m0;++i){
            (*m_tableEntry)[i].clear();
            (*m_tableEntry)[i] = std::move((*tmpT)[i]);
        }
        delete tmpT;
    }
}

const bool PerfectHashTable::Get(uint32_t k){
    auto index = m_mH(k);
    for(auto &i : (*m_tableEntry)[index]){
        if(i == k)return true;
    }
    return false;
}

void PerfectHashTable::Set(uint32_t k){
    Rehash(); // Check if table has too many elements
    auto i = m_mH(k);
    if(!Get(k)){(*m_tableEntry)[i].insert_after((*m_tableEntry)[i].end(),k);}
}