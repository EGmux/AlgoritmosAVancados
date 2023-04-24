#ifndef VAN_ENDE_BOAS_H
#define VAN_ENDE_BOAS_H

#include <cstddef>
#include <cstdint>
#include <math.h>
#include <memory>
#include <vector>

struct VEBTree{
        std::vector<VEBTree*> m_subtrees;
        VEBTree* m_summary;
        uint32_t m_bitsize;
        int32_t min{-1};
        int32_t max{-1}; // equivalent to nil, cast will be needed
        
        VEBTree(const uint32_t universeSize):m_subtrees(NULL),m_summary(NULL),m_bitsize(universeSize){
            m_subtrees.resize(m_bitsize>>1); // resize because 0 is indeed the base case for an empty VEB
        };
    };
    
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
    void insertion(VEBTree* parentNode , uint32_t valueToBeInserted);
    
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

    /* 
    * @brief Return m_vebTREE used to initialize the tree for the first call of the constructor
    * @params None
    * @return m_vebTREE
    */
    VEBTree* get_VEB();
    
     VanEndeBoas(const uint32_t universeSize,  VEBTree* parentNode);
    
private:
    VEBTree* m_vebTREE;

    /* 
    *   @brief Insert a value in an empty cluster of the VEB
    *   @params valueToBeInserted the value to be inserted, note that
    *   the min and max fields of the struct will be the same
    *   parentNode pointer to node that will have it max and min fields updated.
    *   @return None
     */
    static void emptyTreeInsertion(const uint32_t POSITION, VEBTree* parentNode);

    /* 
    *   @brief Return the position where a value can be inserted in a cluster 
    *   @params valueToBeInserted the value that will be inserted in a specific cluster
    *   parentNode a pointer to the cluster where the insertion will happen.
    *   @return position in the cluster.
     */
    static uint32_t positionInCluster(const uint32_t valueToBeInserted, VEBTree* parentNode);

    /* 
    *   @brief Return the cluster where a value can be inserted
    *   @params valueToBeInserted the value that will be inserted in a specific cluster
    *   parentNode a pointer to the cluster where the insertion will happen.
    *   @return position in the cluster.
     */
    static uint32_t positionOfCluster(const uint32_t valueToBeInserted, VEBTree* parentNode);
};

#endif    // VAN_ENDE_BOAS_H