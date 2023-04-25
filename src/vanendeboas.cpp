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
    return computeValue(clusterNumNew, w, clusterPosNew);
}

void VanEndeBoas::Insertion(VEBTree* parentNode, uint32_t valueToInsert){
    /* if current node is empty, insert the value without repercussion */
    if(parentNode->min == NIL){
        parentNode->min = parentNode->max = valueToInsert;
    }
    else{
        /* value to insert becomes the new current node min, we need to propagante such min and insert somewhere else */
        if(valueToInsert < parentNode->min){
            auto tmpxch = parentNode->min;
            parentNode->min = valueToInsert;
            valueToInsert = tmpxch;
        }
        /* if value to insert is not the cluster min it could be the cluster max  */
        if(valueToInsert > parentNode->max){
            parentNode->max = valueToInsert;
        }
        /* if one of the pointed clusters is empty we can put the value there and update the summary, note the update requires a recursive call */
        auto [clusterNum, clusterPos] = GetClusterCoordinates(valueToInsert, parentNode);
        if(parentNode->m_subtrees[clusterNum]->min == NIL){
            Insertion(parentNode->m_summary, clusterNum);
        }
        /* if the above condition is true, insertion is directly in the next cluster so o(1), else it'll be the only recursive call */
        Insertion(parentNode->m_subtrees[clusterNum], clusterPos);
    }
}

void VanEndeBoas::Removal(uint32_t valueToFind, VEBTree *parentNode){
    auto [clusterNum, clusterPos] = GetClusterCoordinates(valueToFind, parentNode);
    auto w =parentNode->m_bitsize;
    /* if the value to remove is the min of a node it must be recomputed  */
    if(valueToFind == parentNode->min){
        /* we find the first non empty cluster in the summary min field */
        clusterNum = parentNode->m_summary->min;
        /* such cluster is empty, then we can't even update the cluster's minimum */
        if(clusterNum == NIL){
            parentNode->min = NIL;
            return;
        }
        auto clusterPosNew = parentNode->m_subtrees[clusterNum]->min;
        /*  it must be the case that the cluster has at least one element to be the new mininmum*/
        valueToFind = parentNode->min = computeValue(clusterNum, w, clusterPosNew);
    }
    /* we now neew to update the clusters *
     did the cluster become empty after the update, we need to update the summary then */
    Removal(valueToFind, parentNode);
    if(parentNode->m_subtrees[clusterNum]->min == NIL){
        Removal(valueToFind, parentNode->m_summary);
    }
    /* we still need to update the node's max, in this case is mininum because no other element is present  */
    if(parentNode->m_summary->min == NIL){
        parentNode->max = parentNode->min; // any other element besides the minimum?
    }
    else{
        /* Summary is not empty so the only logical choice for max is the last non empty cluster  */
        auto clusterNumNew = parentNode->m_summary->max; // this is the last non empty cluster
        auto clusterPosNew = parentNode->m_subtrees[clusterNumNew]->max;
        parentNode->max = computeValue(clusterNumNew, w, clusterPosNew);
    }
}