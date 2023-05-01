#ifndef PERFECT_HASH_TABLE_H
#define PERFECT_HASH_TABLE_H
#include <cstdint>
#include <vector>
#include <list>

typedef std::vector<std::vector<uint32_t>> SecondLvTable;
        
typedef std::vector<std::vector<std::vector<uint32_t>>*> PerefctTable; // new level 1 table aftec the perfect hashing

typedef std::vector<std::list<uint32_t>*> FirstLvTable;

typedef uint32_t (*Mht)(uint32_t,bool);

typedef uint32_t(*MGht)(uint32_t,uint32_t);

typedef uint32_t (*RNG)();

struct PerfectHashTable{
    /* We need the multiple tables, an vector of linked lists and a function pointer */
    FirstLvTable m_tableEntry; // pointer, size of linked list, note that will be deleted after perfect hashing
    PerefctTable m_newTable;
    SecondLvTable m_tables; // level2 table

//methods
    //BasicHashing
    std::pair<int32_t,int32_t> Set(uint32_t k);
    std::pair<bool,uint32_t> Get(uint32_t k);
    void Rehash();
    uint32_t h1(uint32_t k,bool flag);

    //PerfectHashing
    uint32_t PerfectHashingSearch(PerfectHashTable* t, Mht h, std::vector<MGht> g, uint32_t k);
    void BuildPerfectHashing();

    // fields
    Mht m_mH; // first one use this
    std::vector<MGht> m_gH;// second one use this
    RNG m_rng;
    uint32_t m_u;
    uint32_t m_m0;
    uint32_t m_p;
    uint32_t m_numKeys;
    uint32_t m_seed;
    uint32_t m_a;
    uint32_t m_b;
    bool m_isSeed;

    //constructors
    explicit PerfectHashTable( uint32_t u, uint32_t m0, uint32_t p, RNG rng,uint32_t seed);
};


#endif //PERFECT_HASH_TABLE_H