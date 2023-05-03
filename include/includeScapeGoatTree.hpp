#ifndef SCAPE_GOAT_TREE_H
#define SCAPE_GOAT_TREE_H

#include <cstdint>
#include <utility>

struct node{
    node* left{nullptr};
    node* right{nullptr};
    uint32_t key;
    node(node*l,node*r,uint32_t k):left(l),right(r),key(k){};
};

struct out{
    node* root{nullptr};
    int32_t newNodes{0};
    int32_t n{0};
    bool isRebuild{false};
    int32_t dist;
};

struct ScapeGoatTree{
    std::pair<int32_t,int32_t> insert(uint32_t k, float alpha);
    int32_t query(uint32_t k);


    std::pair<int32_t,node*> m_search(uint32_t k);
    out sSGIns(node* root, int32_t depth, int32_t n,float a, int32_t k);
    bool unbalanced(float a, uint32_t n, uint32_t i);
    node* rebuild(node* root, uint32_t n);
    node* flatten(node* root, node* head);
    node* build(node* head, uint32_t n);
    

    //fields
    node* root{nullptr};
    uint32_t size;
};

#endif //SCAPE_GOAT_TREE_H