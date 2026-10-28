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

    node<int>* target_node1_ptr = tree_search<int>(tree1, 13, false);
    std::cout << "iterative search test" << std::endl << target_node1_ptr->value << std::endl;

    node<int>* target_node2_ptr = tree_search<int>(tree1, 16, true);
    std::cout << "recursive search test" << std::endl << target_node2_ptr->value << std::endl;

    node<int>* successor_node_ptr = successor<int>(target_node1_ptr);
    std::cout << "successor test" << std::endl << successor_node_ptr->value << std::endl;

    node<int>* predeccessor_node_ptr = predeccessor<int>(target_node2_ptr);
    std::cout << "predeccessor test" << std::endl << predeccessor_node_ptr->value << std::endl;

    tree<string> tree2;
    tree_insert<string>(tree2, "hello");
    tree_insert<string>(tree2, "good");
    tree_insert<string>(tree2, "fun");
    tree_insert<string>(tree2, "funny");
    tree_insert<string>(tree2, "data");
    tree_insert<string>(tree2, "structure");

    node<string>* target_node3_ptr = tree_search<string>(tree2, "fun", false);
    std::cout << "iterative search test" << std::endl << target_node3_ptr->value << std::endl;

    node<string>* target_node4_ptr = tree_search<string>(tree2, "fun", true);
    std::cout << "recursive search test" << std::endl << target_node4_ptr->value << std::endl;

    return 0;
}