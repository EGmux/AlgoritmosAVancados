#include "../include/vanendeboas.hpp"
#include <algorithm>
#include <cstdint>
#include <cmath>
#include <memory>
#include <sys/types.h>
#include <tuple>

#define NIL -1
#define computeValue(c,w,i) ((c << (w >> 1)) | i)

    /* 
    *   In the first call we get the root node, m_vebTREE, initialize it
    *   then we call the constructor once to initialize the summary node
    *   and the second time in hde for loop to initialize each cluster. The
    *   end condition of the recursion is whenever bitsize is equal to 1
    *   that would result in an empty leaf node.
    */
VanEndeBoas::VanEndeBoas(const uint32_t universeSize, VEBTree* parentNode){
    if(universeSize > 1){
        const uint32_t clusterGroups = sqrt(universeSize);
        parentNode = new VEBTree(universeSize);
        VanEndeBoas(clusterGroups, parentNode->m_summary); // initialize the summary for each node
        for(auto i{0}; i < clusterGroups;++i){
            VanEndeBoas(clusterGroups, parentNode->m_subtrees[i]); // initialize each cluster node
        }
    }
}

    /* We use this to initialize the above constructor */
VEBTree* VanEndeBoas::get_VEB(){return m_vebTREE;}

clusterCoordinates VanEndeBoas::GetClusterCoordinates(const uint32_t valueToBeInserted, VEBTree* parentNode){
    auto w = parentNode->m_bitsize;
    return clusterCoordinates{(valueToBeInserted >> (w >> 1)),(valueToBeInserted && (( 1 << (w >> 1)) -1))};
}
/* Below implementations were heavily inspired by this YT video: https://www.youtube.com/watch?v=q5QBydFU3GU */
uint32_t VanEndeBoas::Succ(VEBTree* parentNode, const uint32_t valueToFind){
    /* VEB global min is less than value to find, thus VEB global min must be the succesor */
    if(valueToFind < parentNode->min){
        return parentNode->min;
    }
    /* Value to find is less that max of cluster, must be a value between them */
    auto [clusterNum, clusterPos] = GetClusterCoordinates(valueToFind, parentNode);
    auto w = parentNode->m_bitsize;
    if(clusterPos < parentNode->m_subtrees[clusterNum]->max){
        auto clusterPosNew = Succ(parentNode->m_subtrees[clusterNum], clusterPos);
        return computeValue(clusterNum, w, clusterPosNew);
    }
    /* Value to find is max of cluster or the next cluster, we need to traverse the summary to find the next non empty cluster  */
    auto clusterNumNew = Succ(parentNode->m_summary, clusterNum);
    auto clusterPosNew = parentNode->m_subtrees[clusterNumNew]->min;
    return (clusterNum << (w >> 1)) | clusterPosNew;
}
