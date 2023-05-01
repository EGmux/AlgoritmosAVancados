#ifndef PERFECT_HASH_TABLE_H
#define PERFECT_HASH_TABLE_H
#include <cstdint>
#include <vector>
#include <list>

        
typedef std::vector<std::vector<uint32_t>*> SecondLvTable; // new level 1 table aftec the perfect hashing

typedef std::vector<std::list<uint32_t>*> FirstLvTable;

typedef uint32_t (*Mht)(uint32_t,bool);

typedef uint32_t(*MGht)(uint32_t,uint32_t);

typedef uint32_t (*RNG)();

typedef std::pair<std::vector<std::pair<uint32_t,uint32_t>>,std::vector<uint32_t>> miniTables;

struct PerfectHashTable{
    /* We need the multiple tables, an vector of linked lists and a function pointer */
    FirstLvTable m_tableEntry; // pointer, size of linked list, note that will be deleted after perfect hashing
    SecondLvTable m_newTable;

//methods
    //BasicHashing
    std::pair<int32_t,int32_t> Set(uint32_t k);
    std::pair<bool,uint32_t> Get(uint32_t k);
    void Rehash();
    uint32_t h1(uint32_t k,bool flag);
    uint32_t h2(uint32_t k, uint32_t mi, bool flag);

    //PerfectHashing
    std::pair<int32_t,int32_t> PerfectHashingSearch(uint32_t k);
    void BuildPerfectHashing();

    // fields
    std::vector<MGht> m_gH;// second one use this
    RNG m_rng;
    uint32_t m_u;
    uint32_t m_m0;
    miniTables m_pt;
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