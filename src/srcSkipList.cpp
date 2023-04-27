#include "../include/includeSkipList.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iterator>
#include <map>
#include <utility>

USkipList::USkipList(int32_t nodeHeight):m_height((nodeHeight)){
    m_nodes.resize(nodeHeight);
};

std::pair<uint32_t, uint32_t> USkipList::Search(USkipList *L, uint32_t key) {
    auto P = Precursors(L, key); // return the list of precursors, note that P[0] is actually the last element to be filled
    std::map<USkipList*, USkipList*> PMap;
    for(auto &i: P){
        PMap[i] = i; //this remove repeated pointers
    }
    if (P[0]->m_nodes[0] != nullptr && P[0]->m_nodes[0]->m_key == key) { // start from the candidate predecessor, check if indeed it is
        return std::pair<uint32_t, uint32_t> {PMap.size()+1, P[0]->m_nodes[0]->m_height}; 
    } else 
        return std::pair<uint32_t, uint32_t> {PMap.size()+1, 0}; 
}

std::vector<USkipList*> USkipList::Precursors(USkipList *L, uint32_t key) {
    std::vector<USkipList*> P; // create a vector for the list of precursors
    P.resize(L->m_height);
    auto cur = L; // start from the head node
    for (int32_t l {(int32_t)L->m_height-1}; l > -1; --l) { // start from the top of the head node and repeat until you get to the end of that height or find a larger key
        while (cur->m_nodes[l] != nullptr && cur->m_nodes[l]->m_key < key) {
            cur = cur->m_nodes[l]; // keep going to the next node in that height
        }
        P[l] = cur;
    }
    return P;
}

uint32_t USkipList::RandomHeight(USkipList *L, uint32_t(*RNG)()) {
    auto l = 1;
    while (((RNG() % 100 ) < 50) && l < MaxHeight(L)){ // passing a function pointer so we can update the state in main
        l = l + 1;
    }
    return l;
}

uint32_t USkipList::MaxHeight(USkipList *L) {
    return L->m_height + 1;
}

bool USkipList::Delete(USkipList **L, uint32_t key) {
    auto P = (*L)->Precursors(*L, key);
    // couldn't find node
    if (P[0]->m_nodes[0] == nullptr || P[0]->m_nodes[0]->m_key != key) {
        return false;
    }
    auto N = P[0]->m_nodes[0];    // receive the target node address
    for(auto i{0}; i < N->m_height; ++i){
        P[i]->m_nodes[i] = N->m_nodes[i];
    }
    while ((*L)->m_height > 1 && (*L)->m_nodes[(*L)->m_height - 1] == nullptr) {    // remove empty heights
        (*L)->m_height -= 1;
    }
    return true;
}

bool USkipList::Insert(USkipList **L, uint32_t key,  uint32_t(*RNG)()) {
    auto P = Precursors(*L, key);
    // value already in the skiplist
    if (P[0]->m_nodes[0] != nullptr && P[0]->m_nodes[0]->m_key == key) {
        return false;
    }
    auto h = RandomHeight(*L,RNG);  
    if (h > (*L)->m_height) {
        (*L)->m_nodes.resize(h);
        auto increase = h - (*L)->m_height;
        for(auto i{0}; i < increase; ++i) {
            P.push_back(*L);
        }
        (*L)->m_height = h;
    }
    // New node, filling it with null, notice that is not connected to anything at this point
    auto N = new USkipList((h));
    N->m_key = key;
    // now we insert it in the skiplist start from the bottom until the maximum height, that is
    // insert in each "height" of the skippedlist
    for(auto i{0}; i < h; ++i){
        N->m_nodes[i] = P[i]->m_nodes[i];
        P[i]->m_nodes[i] = N;
    }
    return true;
}
