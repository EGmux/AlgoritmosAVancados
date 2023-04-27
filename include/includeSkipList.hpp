#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <cstdint>
#include <vector>
#include <map>

struct USkipList{
    uint32_t m_key;
    uint32_t m_height;
    std::vector<USkipList*> m_nodes; // each pointer points to the next element in their respective height
    USkipList* precursor{nullptr};

    std::pair<uint32_t,uint32_t> Search(USkipList* L, uint32_t key);
    std::map<USkipList*, std::pair<USkipList*,uint32_t>> Precursors(USkipList* L, uint32_t key);
    bool Insert(USkipList** L, uint32_t key, uint32_t(*)());
    uint32_t RandomHeight(USkipList* L, uint32_t(*RNG)());
    uint32_t MaxHeight(USkipList* L);
    bool Delete(USkipList** L, uint32_t key);
    USkipList(int32_t nodeHeight);
};



#endif //SKIP_LIST_H