#include "../include/includePerfectHashing.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <list>
#include <iterator>
#include <sys/types.h>
#include <utility>

PerfectHashTable::PerfectHashTable(uint32_t u, uint32_t m0, uint32_t p, RNG rng, uint32_t seed):m_rng(rng),m_u(u),m_m0(m0),m_p(p),m_seed(seed),m_isSeed(true),m_numKeys(0){
    auto mNewTableTmp = new FirstLvTable;
    mNewTableTmp->resize(m_m0);
    m_tableEntry = mNewTableTmp;
    GenHash1();
};

void PerfectHashTable::GenHash1(){
    uint32_t a = !m_isSeed?(1 + m_rng()%(m_p-1)):(m_isSeed=false,(1+m_seed)%(m_p-1)); // deal with the annoying X[0]
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
    auto isRehash = 2*m_numKeys>m_tableEntry->capacity() ?true:false;
    if(isRehash){
        m_m0 = (m_m0 << 2) + 1; // increase the size
        auto tmpT=new FirstLvTable;  //need to allocate in the heap
        tmpT->resize(m_m0);
        GenHash1(); // P=2^31 -1, mutates m_mH
        for(auto &i: *m_tableEntry){ // acces the indexes of the hashtable
            for(auto &j : *i){ // access the entries in the linked list
                auto newi = m_mH(j);
                if(tmpT[newi].empty()){ //guarantee no segfault
                    auto fwdTmp = new std::list<uint32_t>;
                    (*tmpT)[newi] = fwdTmp;
                }
                (*tmpT)[j]->push_back(j);
            }
        }
        m_tableEntry->reserve(m_m0); //so we don't waste our previous capacity
        for(auto i{0}; i < m_m0;++i){
            (*m_tableEntry)[i]->clear(); //can't use clear here, going to segfault
            (*m_tableEntry)[i]= (*tmpT)[i];
        }
    }
}

const bool PerfectHashTable::Get(uint32_t k){
    auto index = m_mH(k);
    for(auto &i : *(*m_tableEntry)[index]){
        if(i == k)return true;
    }
    return false;
}

std::pair<int32_t,int32_t> PerfectHashTable::Set(uint32_t k){
    Rehash(); // Check if table has too many elements
    auto i = (int32_t)m_mH(k);
    auto j = m_tableEntry[i].size();
    if(j==0){
        auto tmpFL = new std::list<uint32_t>;
        (*m_tableEntry)[i] = tmpFL;
    }
    if(!Get(k)){(*m_tableEntry)[i]->push_back(k),m_numKeys++;} // count only before the insertion!
    else{
        j =i = -1;
    }
    return std::pair<int32_t,int32_t>(i,j);
}