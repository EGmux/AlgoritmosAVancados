#ifndef SCAPE_GOAT_TREE_H
#define SCAPE_GOAT_TREE_H

#include <cstdint>
#include <utility>

struct node{
    node* left{nullptr};
    node* right{nullptr};
    uint32_t key;
};

struct out{
    node* root{nullptr};
    uint32_t newNodes{0};
    uint32_t n{0};
    bool isRebuild{false};
    uint32_t dist;
};

struct alpha{
    uint32_t num{0};
    uint32_t deno{1};
};

struct ScapeGoatTree{
    std::pair<int32_t,int32_t> insert(uint32_t k);
    int32_t query(uint32_t k);


    std::pair<int32_t,node*> m_search(uint32_t k);
    out sSGIns(node* root, uint32_t depth, uint32_t n,alpha a, uint32_t k);
    bool unbalanced(alpha a, uint32_t n, uint32_t i);
    node* rebuild(node* root, uint32_t n);
    node* flatten(node* root, node* head);
    node* build(node* head, uint32_t n);
    

    //fields
    node* root{nullptr};
};

#endif //SCAPE_GOAT_TREE_H