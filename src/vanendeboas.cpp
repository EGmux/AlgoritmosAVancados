#include "../include/vanendeboas.hpp"
#include <algorithm>
#include <cstdint>
#include <cmath>
#include <memory>

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
VEBTree* VanEndeBoas::get_Veb(){return m_vebTREE;}

