#include "../include/includePerfectHashing.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <sys/types.h>
#include <utility>

PerfectHashTable::PerfectHashTable(uint32_t u, uint32_t m0, uint32_t p, RNG rng, uint32_t seed):
        m_rng(rng),
        m_u(u),
        m_m0(m0),
        m_p(p),
        m_seed(seed),
        m_isSeed(true),
        m_numKeys(0) {
    m_tableEntry.resize(m_m0);
    GenHash1();
};

void PerfectHashTable::GenHash1() {
    static auto s_acc{0};
    uint32_t a = !m_isSeed ?
                     (1 + m_rng() % (m_p - 1)) :
                     (m_isSeed = false, (1 + m_seed) % (m_p - 1));    // deal with the annoying X[0]
    uint32_t b = m_rng() % m_p;
    auto u = m_u;
    auto p = m_p;
    auto m0 = m_m0;

    // read this
    // https://stackoverflow.com/questions/7852101/c-lambda-with-captures-as-a-function-pointer
    // Zhang's answer
    static auto impl = [a, b, u, m0, p](uint32_t k) {
        return (((a * k + b) % p) % m0);
    };
    m_mH = [](uint32_t k) {
        return impl(k);
    };
};

void PerfectHashTable::Rehash() {
    auto isRehash = 2 * m_numKeys > m_tableEntry.capacity() ? true : false;
    if (isRehash) {
        m_m0 = (m_m0 << 1) + 1;          // increase the size
        auto tmpT = new FirstLvTable;    // need to allocate in the heap
        tmpT->resize(m_m0);
        GenHash1();    // P=2^31 -1, mutates m_mH
        for (auto i : m_tableEntry) {
            if (i != nullptr) {
                for(auto j : *i){
                    auto newi = m_mH(j);
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
    auto index = m_mH(k);
    uint32_t acc {0};
    for (auto i : *m_tableEntry[index]) {
        if (i == k)
            return {true, acc};
        acc++;
    }
    return {false, m_tableEntry[index]->size()};
}

std::pair<int32_t, int32_t> PerfectHashTable::Set(uint32_t k) {
    Rehash();    // Check if table has too many elements
    uint32_t i = (int32_t) m_mH(k);
    std::pair<bool, uint32_t> j;
    auto isPresent {true};
    if (m_tableEntry[i] == nullptr) {
        auto tmpFL = new std::list<uint32_t>;
        m_tableEntry[i] = tmpFL;
    }
    if (j = Get(k), !j.first) {    // means false
        m_tableEntry[i]->push_back(k), m_numKeys++;
        isPresent = false;
    }
    return {i, j.second};
}