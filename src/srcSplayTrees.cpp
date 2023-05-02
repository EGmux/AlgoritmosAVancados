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

node* SplayTree::m_rotateL(node *x){
    auto p = x->par;
    auto r = x->right;
    auto rleft = r!=nullptr?r->left:nullptr;
    x->right = rleft;
    rleft!=nullptr?rleft->par=x:rleft;
    r!=nullptr?x->par=r,r->par=p,r->left=x:r;
    p->left==x?p->left=r:p->right=r;
    return r;
}

node* SplayTree::m_rotateR(node *x){
    auto p = x->par;
    auto r = x->left;
    auto rright = r!=nullptr?r->right:nullptr;
    x->left=rright;
    rright!=nullptr?rright->par=x:rright;
    r!=nullptr?x->par=r,r->right=x:r;
    p->left==x?p->left=r:p->right=r;
    return r
}