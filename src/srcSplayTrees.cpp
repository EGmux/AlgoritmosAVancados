#include "../include/includeSplayTrees.hpp"
#include <cstdint>

SplayTree::SplayTree()=default;

int32_t nodeInsert(node* x, uint32_t k, int32_t d){
    if(x->key < k){ 
        if(x->left==nullptr){
            auto n = new node;
            x->left = n,x->left->key=k;
            return d;
        }else{
            nodeInsert(x->left, k, d+1);
        }
    }else if(x->key > k){
        if(x->right == nullptr){
            auto n = new node;
            x->right = n,x->right->key=k;
            return d;
        }
            nodeInsert(x->right, k, d+1);
    }
    else{ // must means that x->key == k
        return -1;
    }
}

int32_t SplayTree::insert(uint32_t k){
    //insertion is the same as BST
    auto d = -1;
    if(root == nullptr){
        auto n = new node;
        root = n,root->key = k,d=0;
    }
    else if(root->key < k && root->key != k){
        d  = nodeInsert(root,k,1);
    }
    return d;
}

