#include <cstdio>
#include <iostream>
#include "bst_node.h"
#include "bst_operation.h"

int main(){
    tree<int> tree1;
    tree_insert(tree1, 15);
    tree_insert(tree1, 6);
    tree_insert(tree1, 18);
    tree_insert(tree1, 3);
    tree_insert(tree1, 7);
    tree_insert(tree1, 17);
    tree_insert(tree1, 20);
    tree_insert(tree1, 2);
    tree_insert(tree1, 4);
    tree_insert(tree1, 13);
    tree_insert(tree1, 9);
    tree_insert(tree1, 16);

    node<int>* target_node1_ptr = tree_search<int>(tree1, 6, false);
    node<int>* target_node2_ptr = tree_search<int>(tree1, 15, true);
    node<int>* target_node3_ptr = tree_search<int>(tree1, 13, true);

    tree_delete(tree1, target_node1_ptr);
    vector<int> result1 = preorder_walk(tree1);
    for(auto i : result1){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    tree_delete(tree1, target_node2_ptr);
    vector<int> result2 = preorder_walk(tree1);
    for(auto i : result2){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    tree_delete(tree1, target_node3_ptr);
    vector<int> result3 = preorder_walk(tree1);
    for(auto i : result3){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    return 0;
}