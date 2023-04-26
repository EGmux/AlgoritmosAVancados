#ifndef VAN_ENDE_BOAS_H
#define VAN_ENDE_BOAS_H

#include <cstddef>
#include <cstdint>
#include <math.h>
#include <memory>
#include <utility>
#include <vector>

struct VEBTree{
        std::vector<VEBTree*> m_subtrees;
        VEBTree* m_summary;
        uint32_t m_bitsize;
        int32_t min{-1};
        int32_t max{-1}; // equivalent to nil, cast will be needed
        
        VEBTree(const uint32_t universeSize):m_summary(NULL),m_bitsize(universeSize){
            if(m_bitsize>2){
            m_subtrees.reserve(floor(sqrt(m_bitsize))); // reserve because we'll pushback later, and this speedup things
            m_subtrees.resize(floor(sqrt(m_bitsize)));
            }
        };
    };

typedef std::pair<uint32_t,uint32_t> clusterCoordinates;

class VanEndeBoas {
public:

    /* 
    *   @brief Given a valid node insert into the VEB in one of the existing nodes
    *   such that each node has a partition of the universe set interpreted as a bitvector
    *   that is the insertion maps to an unique position in the universe set thus an unique subtree
    *   per tree traversal.
    *   @params valueToBeInserted the value to be inserted in the VEB.
    *   parentNode the VEB tree being current traversed
    *   @return None
     */    
     uint32_t Insertion(VEBTree** parentNode , uint32_t valueToInsert, VEBTree* ancestralNode);
    
    /*
    *   @brief Given a present value in the VEB find it succesor, to
    *   do so check that either the current node has the next bit set or 
    *   that the next next node with a bit set to the right has it.
    *   @params valueToFind the value to check for a sucessor
    *   parentNode the VEB tree being current traversed
    *   @returns succ the succesor of valueToFind
     */
     int32_t Succ(VEBTree* parentNode,const uint32_t valueToFind);

    /* 
    *   @brief Given a present value in the VEB remove it, to do so check that
    *   the value is present and set it bit to 0, then update the summary field 
    *   of current and ancestral nodes if needed.
    *   @params valueToFind the value to remove
    *   @return None
    * */
     uint32_t Removal( uint32_t valueToFind, VEBTree** parentNode);


     /* 
     *  @brief Return depth after previous operation, note that after returning depth is reset
     *  @params None 
     *  @return None
     *
      */
     uint32_t returnDepth();

    VanEndeBoas(const uint32_t universeSize, VEBTree** parentNode);
    
    
private:

    uint32_t m_depth{1};

    /* 
    *   @brief Return the position where a value can be inserted also the cluster num
    *   @params valueToBeInserted the value that will be inserted in a specific cluster
    *   parentNode a pointer to the cluster where the insertion will happen.
    *   @return tuple<position,clusterNum> 
     */
     static clusterCoordinates GetClusterCoordinates(const uint32_t valueToBeInserted, VEBTree* parentNode);

    /* 
    * @brief Reset m_depth to 1, that means the root depth
    * @params None
    * @return None
     */
     void resetDepth();
};

#endif    // VAN_ENDE_BOAS_H