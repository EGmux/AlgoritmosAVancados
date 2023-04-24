#include "../include/vanendeboas.hpp"
#include <algorithm>
#include <cstdint>
#include <cmath>
#include <memory>
#include <sys/types.h>

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

 void VanEndeBoas::emptyTreeInsertion(const uint32_t POSITION, VEBTree* parentNode){
    parentNode->max = parentNode->min = (uint32_t)POSITION;
}

/* what cluster partition is located, between [0,sqrt(bitsize)] */
uint32_t VanEndeBoas::positionOfCluster(const uint32_t valueToBeInserted, VEBTree* parentNode){
    return floor(valueToBeInserted/sqrt(parentNode->m_bitsize));
}

/* where is located in the cluster partition, between [0,sqrt(bitsize)] */
uint32_t VanEndeBoas::positionInCluster(const uint32_t valueToBeInserted, VEBTree* parentNode){
    return valueToBeInserted%(uint32_t)sqrt(parentNode->m_bitsize);
}

    /* To fill the VEB we do the following we see if the value to be inserted is less
    *  than the current minimum node value, assuming it is we exchange it and propagate the mininum
    *  value to a child node until we can insert it, if the node is empty we also update the 
    *   associated summary. If not empty no update to summary is nedede, because the sumary
    *   must have been updated in a past insertion/deletion.
    */
void VanEndeBoas::insertion(VEBTree* parentNode ,uint32_t valueToBeInserted){
    auto minVal = parentNode->min;
    if(minVal==(-1)){
        emptyTreeInsertion(valueToBeInserted, parentNode);
        /* current node is not empty */
    }else if(valueToBeInserted < parentNode->min){
        auto tmpxchg = minVal;
        parentNode->min=(uint32_t)valueToBeInserted;
        valueToBeInserted=tmpxchg;
    }
    /* propagating the previous minvalue until we can insert it */
    if(parentNode->m_bitsize==2){
        /* means the current node is empty, we can insert here */
        auto [clusterNum, clusterPosition] = std::pair<uint32_t,uint32_t>(positionOfCluster(valueToBeInserted,parentNode),positionInCluster(valueToBeInserted,parentNode));
        if(/* code to find minimum == -1*/2){
            /* here we update the summary associated with the empty node */
            insertion(parentNode->m_summary,clusterNum);
            emptyTreeInsertion(clusterPosition,parentNode->m_subtrees[clusterNum]); 
        }
        /* cluster is not empty and summary is already updated */
        else{
            insertion(parentNode->m_subtrees[clusterNum],clusterPosition);
        }
        if(valueToBeInserted > parentNode->max){
            parentNode->max = valueToBeInserted;
        }
    }
}

