#include "../include/includeScapeGoatTree.hpp"
#include <cstdint>
#include <math.h>

std::pair<int32_t,int32_t> ScapeGoatTree::insert(uint32_t k, float alpha ){
    auto [r,added,a,b,c] = sSGIns(root, 0, size, alpha, k);
    size+=added;
}

out ScapeGoatTree::sSGIns(node *root, int32_t depth, int32_t n, float a, int32_t k){
    if(root == nullptr){
        auto N = new node(nullptr,nullptr,k);
        auto chg = depth > floor(log2(n+1));
        return {N,1,1,chg,0};
    }else if(root->key == k){
        return {root,0,-1,false,-1};
    }else if(k < root->key){
        
    auto [rl, add, ne, chg, dist] = ScapeGoatTree::sSGIns(root->left, int32_t depth, int32_t n, float a, int32_t k)
    }
}

int* tree();