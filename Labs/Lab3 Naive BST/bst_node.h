#pragma once
#include <cstdio>

template <typename T>
class node;

template <typename T>
class tree{
    public:
    node<T>* root;
    tree(){
        root = nullptr;
    }
};

template <typename T>
class node{
    public:
    T value;
    node* parent;
    node* left_child;
    node* right_child;

    node(T val, node* p=nullptr, node* lc=nullptr, node* rc=nullptr){
        value = val;
        parent = p;
        left_child = lc;
        right_child = rc;
    }
};
