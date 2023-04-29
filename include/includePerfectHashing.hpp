#ifndef PERFECT_HASH_TABLE_H
#define PERFECT_HASH_TABLE_H
#include <cstdint>
#include <vector>

typedef std::vector<std::vector<uint32_t>> SecondLvTable;
        
typedef std::vector<std::vector<std::vector<uint32_t>>*> PerefctTable; // new level 1 table aftec the perfect hashing

typedef std::vector<std::pair<uint32_t*, uint32_t>> FirstLvTable;

typedef uint32_t (*MHT)(uint32_t k);

typedef uint32_t (*MGHt)(uint32_t u,uint32_t mI, uint32_t p );

typedef uint32_t (*RNG)();

struct PerfectHashTable{
    /* We need the multiple tables, an vector of linked lists and a function pointer */
    FirstLvTable* m_tableEntry; // pointer, size of linked list, note that will be deleted after perfect hashing
    PerefctTable* m_newTable;
    SecondLvTable* m_tables; // level2 table

    //BasicHashing
    void Set(uint32_t k);
    void Rehash();
    MHT GenHash1(uint32_t u, uint32_t m0, uint32_t p, RNG rng);

    //PerfectHashing
    uint32_t PerfectHashingSearch(PerfectHashTable* t, MHT h, std::vector<MGHt> g, uint32_t k);
    void BuildPerfectHashing(std::vector<uint32_t> keys);

    MHT m_mH; // first one use this
    MGHt m_gH;// second one use this
    RNG m_rng;
    explicit PerfectHashTable( uint32_t u, uint32_t m0, uint32_t p, RNG rng);
};


#endif //PERFECT_HASH_TABLE_H