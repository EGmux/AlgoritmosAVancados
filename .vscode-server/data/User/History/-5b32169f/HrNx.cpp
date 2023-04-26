#include "../include/includeSkipList.hpp"
#include <cstdint>
#include <forward_list>

SkipList::SkipList()= default;

bool SkipList::Insertion(uint32_t valueToInsert){
    std::forward_list<uint32_t>* head = m_sentinel->first;
}