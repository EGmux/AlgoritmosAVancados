#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <forward_list> // single linked list
#include <cstdint>
#include <vector>

typedef std::pair<std::forward_list<uint32_t>*,std::vector<std::forward_list<uint32_t>*>> USkiplist;

struct SkipList{
    bool Insertion( uint32_t valueToInsert);
    bool Removal( uint32_t valueToRemove);
    std::pair<uint32_t, uint32_t> Find( uint32_t valueToFind);
    SkipList();
    USkiplist* m_sentinel{nullptr};
};



#endif //SKIP_LIST_H