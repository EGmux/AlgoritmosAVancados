#ifndef SPLAY_TREES_H
#define SPLAY_TREES_H
#include <cstdint>

struct node{
    node* left;
    node* right;
    uint32_t key;
    node* papa;
};
struct SplayTree{
    //Public methods
    SplayTree();
    uint32_t insert(uint32_t k);
    uint32_t query(uint32_t k);

    // Base methods
    node* m_rotateL(node* x);
    node* m_rotateR(node* x);

    // Operational methods
    node* m_zig(node* x);
    node* m_zigzag(node *x);
    node* splay(node* x);

}


#endif //SPLAY_TREES_H