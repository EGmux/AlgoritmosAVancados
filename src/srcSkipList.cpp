#include "../include/includeSkipList.hpp"
#include <cstdint>
#include <cstdlib>
#include <utility>

USkipList::USkipList()= default;

std::pair<uint32_t, uint32_t> USkipList::Search(USkipList *L, uint32_t key) {
    auto P = Precursors(L, key); // return the list of precursors, note that P[0] is actually the last element to be filled
    if (P[0]->m_nodes[0] != nullptr && P[0]->m_nodes[0]->m_key == key) { // start from the candidate predecessor, check if indeed it is
        return std::pair<uint32_t, uint32_t> {P.size(), P[0]->m_height}; 
    } else 
        return std::pair<uint32_t, uint32_t> {P.size(), 0};
}

std::vector<USkipList *> USkipList::Precursors(USkipList *L, uint32_t key) {
    std::vector<USkipList *> P; // create a vector for the list of precursors
    P.resize(L->m_height);    // hopefully all nullptr's
    auto cur = &L[0]; // start from the head node
    for (auto l {L->m_height-1}; l >= 0; --l) { // start from the top of the head node and repeat until you get to the end of that height or find a larger key
        while (cur->m_nodes[l] != nullptr && cur->m_nodes[l]->m_key < key) {
            cur = cur->m_nodes[l]; // keep going to the next node in that height
        }
        P[l] = cur; 
    }
    return P;
}

uint32_t USkipList::RandomHeight(USkipList *L, uint32_t(*RNG)()) {
    auto l = 1;
    while ((RNG() % 100 ) < 50 && l < MaxHeight(L)){ // passing a function pointer so we can update the state in main
        l = l + 1;
    }
    return l;
}

uint32_t USkipList::MaxHeight(USkipList *L) {
    return L->m_height + 1;
}

bool USkipList::Delete(USkipList *L, uint32_t key) {
    auto P = L->Precursors(L, key);
    // couldn't find node
    if (P[0]->m_nodes[0] == nullptr || P[0]->m_nodes[0]->m_key != key) {
        return false;
    }
    auto N = P[0]->m_nodes[0];    // receive the target node address
    for (auto l {0}; l < N->m_height; ++l) {
        P[l]->m_nodes[l] =
            N->m_nodes[l];    // make sure the precursos point to the succ of target node
    }
    while (L->m_height > 1 && L[0].m_nodes[L->m_height - 1] == nullptr) {    // remove empty heights
        L->m_height = L->m_height - 1;
    }
    return true;
}

bool USkipList::Insert(USkipList *L, uint32_t key,  uint32_t(*RNG)()) {
    auto P = Precursors(L, key);
    // value already in the skiplist
    if (P[0]->m_nodes[0] != nullptr && P[0]->m_nodes[0]->m_key == key) {
        return false;
    }
    // value is not in the skip list, do we increase the height of the precursors?
    auto h = RandomHeight(L,RNG);
    if (h > L->m_height) {
        L[0].m_nodes.resize(h);
        for (auto i {0}; i < h; ++i) {
            L[0].m_nodes[i]->m_nodes.push_back(nullptr);    // code might be wrong
            P[i]->m_nodes.resize(h), P[i]->m_nodes[i]->m_nodes.push_back(&L[0]);
        }
        L->m_height = h;
    }
    // New node, filling it with null, notice that is not connected to anything at this point
    auto N = new USkipList;
    N->m_nodes.reserve(h);
    for (auto i {0}; i < h; ++i) {
        N[i].m_nodes.push_back(nullptr);
    }
    N->m_key = key;
    // now we insert it in the skiplist start from the bottom until the maximum height, that is
    // insert in each "height" of the skippedlist
    for (auto l {0}; l < h; ++l) {
        N->m_nodes[l] = P[l]->m_nodes[l];
        P[l]->m_nodes[l] = N;
    }
    return true;
}
