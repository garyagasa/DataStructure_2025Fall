#include "bst_node.h"
#include "bst_operation.h"
#include <random>
#include <string>

int main(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-100, 100);

    tree<int> tree1;
    for(int i = 1; i < 20; i++){
        tree_insert<int>(tree1, dist(gen));
    }

    vector<int> result1 = preorder_walk(tree1);
    for(auto i : result1){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    vector<int> result2 = inorder_walk(tree1);
    for(auto i : result2){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    vector<int> result3 = postorder_walk(tree1);
    for(auto i : result3){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    // ------------------------------------------------------------------------------------------------
    
    tree<string> tree2;
    tree_insert<string>(tree2, "hello");
    tree_insert<string>(tree2, "good");
    tree_insert<string>(tree2, "fun");
    tree_insert<string>(tree2, "funny");
    tree_insert<string>(tree2, "data");
    tree_insert<string>(tree2, "structure");

    vector<string> result4 = preorder_walk(tree2);
    for(auto i : result4){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    vector<string> result5 = inorder_walk(tree2);
    for(auto i : result5){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    vector<string> result6 = postorder_walk(tree2);
    for(auto i : result6){
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}