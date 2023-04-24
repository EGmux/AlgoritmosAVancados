#ifndef VAN_ENDE_BOAS_H
#define VAN_ENDE_BOAS_H

#include <cstdint>
#include <vector>

class VanEndeBoas {
public:

    /* 
    *   @brief Given a valid node insert into the VEB in one of the existing nodes
    *   such that each node has a partition of the universe set interpreted as a bitvector
    *   that is the insertion maps to an unique position in the universe set thus an unique subtree
    *   per tree traversal.
    *   @params valueToBeInserted the value to be inserted in the VEB.
    *   @return None
     */    
    void insertion(const uint32_t valueToBeInserted);
    
    /*
    *   @brief Given a present value in the VEB find it succesor, to
    *   do so check that either the current node has the next bit set or 
    *   that the next next node with a bit set to the right has it.
    *   @params valueToFind the value to check for a sucessor
    *   @returns succ the succesor of valueToFind
     */
    uint32_t succ(const uint32_t valueToFind);

    /* 
    *   @brief Given a present value in the VEB remove it, to do so check that
    *   the value is present and set it bit to 0, then update the summary field 
    *   of current and ancestral nodes if needed.
    *   @params valueToFind the value to remove
    *   @return None
    * */
    void removal(const uint32_t valueToFind);
    
    VanEndeBoas(const std::vector<uint32_t> &universe);
    
private:
    struct VEBTree{
        std::vector<VEBTree*> m_subtrees;
        VEBTree* m_summary;
        uint32_t m_bitsize;
    };
    VEBTree* m_vebTREE;
};

#endif    // VAN_ENDE_BOAS_H