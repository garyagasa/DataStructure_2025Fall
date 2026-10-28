#include <cstdio>
#include "bst_node.h"
#include <vector>
#include <iostream>
using namespace std;

template <typename T>
void tree_insert(tree<T>& t, T new_val){
    node<T>* new_node = new node<T>(new_val);
    // if the tree is empty, corner case
    if(t.root == nullptr){
        t.root = new_node;
        return;
    }

    node<T> *p_ptr;
    node<T> *ptr = t.root;
    while(ptr != nullptr){
        p_ptr = ptr;
        if(new_val > ptr->value){
            ptr = ptr->right_child;
        }
        else{
            ptr = ptr->left_child;
        }
    }

    if(new_val > p_ptr->value){
        p_ptr->right_child = new_node;
        new_node->parent = p_ptr;
    }
    else{
        p_ptr->left_child = new_node;
        new_node->parent = p_ptr;
    }
}

// To-Do: the search algorithm, both in recursive way or iterative way
template <typename T>
node<T>* tree_search(tree<T> t, T key, bool is_recursion=false){
    if(t.root == nullptr){
        throw std::invalid_argument("empty tree, can't search");
    }
    if(is_recursion){
        return tree_search_recursive(t.root, key);
    }
    return tree_search_iterative(t.root, key);
}

template <typename T>
node<T>* tree_search_recursive(node<T>* root, T key){
    if(root == nullptr){
        return NULL;
    }
    if(key < root->value){
        return tree_search_recursive(root->left_child, key);
    }
    else if(key == root->value){
        return root;
    }
    else{
        return tree_search_recursive(root->right_child, key);
    }
}

template <typename T>
node<T>* tree_search_iterative(node<T>* root, T key){
    node<T>* ptr = root;
    while(ptr != nullptr){
        if(key == ptr->value){
            return ptr;
        }
        else if(key < ptr->value){
            ptr = ptr->left_child;
        }
        else{
            ptr = ptr->right_child;
        }
    }
    return NULL;
}

// To-Do
template <typename T>
node<T>* successor(node<T>* source){
    // if there is right subtree
    if(source->right_child != nullptr){
        node<T>* ptr = source->right_child;
        while(ptr->left_child != nullptr){
            ptr=ptr->left_child;
        }
        return ptr;
    }
    // if there isn't right subtree, we go back to the ancestors
    node<T>* p_ptr = source->parent;
    node<T>* ptr = source;
    while(p_ptr != nullptr && p_ptr->right_child == ptr){
        ptr = p_ptr;
        p_ptr = p_ptr->parent;
    }
    return p_ptr;
}   

// To-Do
template <typename T>
node<T>* predeccessor(node<T>* source){
    // if there is left subtree
    if(source->left_child != nullptr){
        node<T>* ptr = source->left_child;
        while(ptr->right_child != nullptr){
            ptr=ptr->right_child;
        }
        return ptr;
    }
    // if there isn't left subtree, we go back to the ancestors
    node<T>* p_ptr = source->parent;
    node<T>* ptr = source;
    while(p_ptr != nullptr && p_ptr->left_child == ptr){
        ptr = p_ptr;
        p_ptr = p_ptr->parent;
    }
    return p_ptr;
}

template <typename T>
void preorder_walk_helper(node<T>* root, vector<T>& result){
    if(root == nullptr) return;
    result.push_back(root->value);
    preorder_walk_helper(root->left_child, result);
    preorder_walk_helper(root->right_child, result);
}

template <typename T>
vector<T> preorder_walk(tree<T>& t){
    vector<T> ret;
    preorder_walk_helper(t.root, ret);
    return ret;
}

template <typename T>
void inorder_walk_helper(node<T>* root, vector<T>& result){
    if(root == nullptr) return;
    inorder_walk_helper(root->left_child, result);
    result.push_back(root->value);
    inorder_walk_helper(root->right_child, result);
}

template <typename T>
vector<T> inorder_walk(tree<T>& t){
    vector<T> ret;
    inorder_walk_helper(t.root, ret);
    return ret;
}

template <typename T>
void postorder_walk_helper(node<T>* root, vector<T>& result){
    if(root == nullptr) return;
    postorder_walk_helper(root->left_child, result);
    postorder_walk_helper(root->right_child, result);
    result.push_back(root->value);
}

template <typename T>
vector<T> postorder_walk(tree<T>& t){
    vector<T> ret;
    postorder_walk_helper(t.root, ret);
    return ret;
}

template <typename T>
void transplant(tree<T>& t, node<T>* u, node<T>* v){
    // if we need to transplant the root
    if(t.root == u){
        t.root == v;
        v->parent = nullptr;
        return;
    }
    // if the u is the left child
    if(u == u->parent->left_child){
        u->parent->left_child = v;
        if(v != nullptr)
            v->parent = u->parent;
    }
    // if the u is the right child
    else{
        u->parent->right_child = v;
        if(v != nullptr)
            v->parent = u->parent;
    }
}

template <typename T>
void tree_delete(tree<T>& t, node<T>* target){
    // if target has no left child
    if(target->left_child == nullptr){
        transplant(t, target, target->right_child);
        return;
    }
    // else if the target has no right child
    else if (target->right_child == nullptr){
        transplant(t, target, target->left_child);
        return;
    }
    // if the target has two child, find the successor, which must be on the right subtree
    node<T>* suc = successor(target);
    if(suc == target->right_child){
        transplant(t, target, suc);
        suc->left_child = target->left_child;
        target->left_child->parent = suc;
        // not operate on the right child of target(it is suc itself and conflicts!!!)
    }
    else{
        transplant(t, suc, suc->right_child);
        transplant(t, target, suc);
        suc->left_child = target->left_child;
        target->left_child->parent = suc;
        suc->right_child = target->right_child;
        target->right_child->parent = suc;
    }
}
