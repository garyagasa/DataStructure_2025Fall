#pragma once
#include <string>

template <typename T>
class node{
    public:
    T value;
    node* parent;
    node* left_child;
    node* right_child;
    bool is_red;
    int height;         /*the height of subtree rooted at this node*/
    std::string satellite;

    node(T val, node* p=nullptr, node* lc=nullptr, node* rc=nullptr, bool is_Red=false, int h=0){
        value = val;
        parent = p;
        left_child = lc;
        right_child = rc;
        is_red = is_Red;
        height = h;
    }

    void set_satellite(std::string sat_data){
        satellite = sat_data;
    }
};
