#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <forward_list> // single linked list
#include <cstdint>
#include <vector>

// first is the horizontal list, second is the "upper" lists
typedef std::pair<std::forward_list<uint32_t>*,std::vector<std::forward_list<uint32_t>*>> USkiplist;

struct SkipList{
    bool Insertion(USkiplist* curList, uint32_t valueToInsert);
    bool Removal(USkiplist* curList, uint32_t valueToRemove);
    std::pair<uint32_t, uint32_t> Find(USkiplist* curList, uint32_t valueToFind);
};



#endif //SKIP_LIST_H