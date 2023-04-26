#include "../include/includeSkipList.hpp"
#include <cstdint>
#include <array>
#include <forward_list>

SkipList::SkipList()= default;

bool SkipList::Insertion(uint32_t valueToInsert){
    auto curNode = m_sentinel->first;
    auto curHeight = m_sentinel->second;
    std::vector<std::vector<uint32_t>> path;
    while(valueToInsert < curNode->front()){

    }
    
}