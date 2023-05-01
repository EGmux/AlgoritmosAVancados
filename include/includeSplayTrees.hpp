#ifndef SPLAY_TREES_H
#define SPLAY_TREES_H
#include <cstdint>

struct node{
    node* left{nullptr};
    node* right{nullptr};
    uint32_t key;
    node* par{nullptr}; //parent
};
struct SplayTree{
    //Public methods
    SplayTree();
    int32_t insert(uint32_t k);
    int32_t query(uint32_t k);

    // Base methods
    node* m_rotateL(node* x);
    node* m_rotateR(node* x);

    // Operational methods
    node* m_zig(node* x);
    node* m_zigzag(node *x);
    node* splay(node* x);

    //fields
    node* root;
}


#endif //SPLAY_TREES_H