#include "../include/includeSplayTrees.hpp"
#include <cstdint>

SplayTree::SplayTree()=default;

int32_t nodeInsert(node* x, uint32_t k, int32_t d){
    if(k < x->key){ 
        if(x->left==nullptr){
            auto n = new node;
            x->left = n,x->left->key=k,x->left->par=x;
            return d;
        }else{
            return nodeInsert(x->left, k, d+1);
        }
    }else if(k > x->key){
        if(x->right == nullptr){
            auto n = new node;
            x->right = n,x->right->key=k,x->right->par=x;
            return d;
        }
            return nodeInsert(x->right, k, d+1);
    }
    return -1;
}

int32_t SplayTree::insert(uint32_t k){
    //insertion is the same as BST
    auto d = -1;
    if(root == nullptr){
        auto n = new node;
        root = n,root->key = k,d=0;
    }
    else if(root->key != k){
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
    r->left = x; //always != nullptr
    r->left=x;
    x->par=r;
    r->par=p;
        if(p!=nullptr){
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
    r->right = x;
    x->par=r;
    r->par=p;
        if(p!=nullptr){
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
        if(x==p->left){
            m_rotateR(g);
            return m_rotateR(p);
        }else{
            m_rotateL(p);
            return m_rotateR(g);
        }
    }
    else{
        if(x==p->right){
            m_rotateL(g);
            return m_rotateL(p);
        }else{
            m_rotateR(p);
            return m_rotateL(g);
        }
    }
}

node* SplayTree::m_splay(node *x){
    while(x->par != nullptr){// that is x is not root-node
        auto g = x->par->par; //before x is root node g will be nullptr
        g==nullptr?m_zig(x):m_zigzag(x); //increment acc twice
    } 
    return x;
}

std::pair<int32_t,node*>SplayTree::m_search(uint32_t k){
    int32_t depth=0;
    auto cur = root;
    while(cur!=nullptr){
        if(cur->key==k){
            return {depth,cur};
        }else{
            depth++,cur = (k < cur->key?cur->left:cur->right);
        }
    }
    return {-1,nullptr};
}

int32_t SplayTree::query(uint32_t k){
    auto x = m_search(k);
    if(x.second!=nullptr){ // x is a node that exists
        root = m_splay(x.second);
    } 
    return x.first;
}