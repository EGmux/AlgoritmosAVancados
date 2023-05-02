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
    if(r!=nullptr){
        x->par=r,r->par=p,r->left=x;
        p->left==x?p->left=r:p->right=r;
    }
    return r;
}

node* SplayTree::m_rotateR(node *x){
    auto p = x->par;
    auto r = x->left;
    auto rright = r!=nullptr?r->right:nullptr;
    x->left=rright;
    rright!=nullptr?rright->par=x:rright;
    if(r!=nullptr){
        x->par=r,r->right=x;
        p->left==x?p->left=r:p->right=r;
    }
    return r;
}

node* SplayTree::m_zig(node *x){
    auto p = x->par;
    return x==p->left?m_rotateR(p):m_rotateL(p);
}

node* SplayTree::m_zigzag(node *x){
    auto p = x->par;
    auto g = p->par; //ancestral of x
    if(p == g->left){
        return x==p->left?m_rotateR(g),m_rotateR(p):m_rotateL(p),m_rotateR(g);
    }
    else{
        return x==p->right?m_rotateL(g),m_rotateL(p):m_rotateR(p),m_rotateL(g);
    }
}

node* SplayTree::splay(node *x){
    int32_t acc=-1;
    while(x->par != nullptr){// that is x is not root-node
        auto g = x->par->par; //before x is root node g will be nullptr
        if(g==nullptr){
            m_zig(x),acc=acc+1;
        }else{
            m_zigzag(x),acc=acc+2; //increment acc twice
        }
    } 
    return {acc,x};
}

std::pair<int32_t,node*>SplayTree::search(uint32_t k){
    int32_t depth=0;
    auto cur = root;
    while(cur!=nullptr){
        if(cur->key==k){
            return {depth,cur};
        }else{
            depth++,cur = (cur->key<k?cur->left:cur->right);
        }
    }
    return {-1,nullptr};
}

int32_t SplayTree::query(uint32_t k){
    auto x = search(k);
    if(x.second!=nullptr){ // x is a node that exists
        root = splay(x.second);
    } 
    return x.first;
}