#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include "../bst/red_black.h"

int main(){
    std::cout << "----------------------Testing Tree Insertion----------------------" << std::endl;
    red_black_tree<int> tree0;
    tree0.tree_insert(10);
    tree0.tree_insert(2);
    tree0.tree_insert(12);
    tree0.tree_insert(4);
    tree0.tree_insert(6);
    tree0.tree_insert(8);
    tree0.tree_insert(1);
    tree0.tree_insert(9);
    tree0.tree_insert(7);
    tree0.tree_insert(3);
    tree0.tree_insert(11);
    tree0.tree_insert(5);
    tree0.breadth_first_walk_print();
    tree0.pre_order_print();
    
    red_black_tree<std::string> tree2;
    tree2.tree_insert("韩国瑜");
    tree2.tree_insert("高雄");
    tree2.tree_insert("发财");
    tree2.tree_insert("发大财");
    tree2.tree_insert("我");
    tree2.tree_insert("就要");
    tree2.tree_insert("出征");
    tree2.tree_insert("秃子");
    tree2.tree_insert("跟着");
    tree2.tree_insert("月亮");
    tree2.tree_insert("走");
    tree2.breadth_first_walk_print();
    tree2.pre_order_print();

    red_black_tree<std::string> tree3;
    tree3.tree_insert("calm", "冷静");
    tree3.tree_insert("keep", "保持");
    tree3.tree_insert("and", "且");
    tree3.tree_insert("carry", "继续");
    tree3.tree_insert("on", "前行");
    tree3.tree_insert("don't", "不要");
    tree3.tree_insert("go", "走");
    tree3.tree_insert("gentle", "温和");
    tree3.tree_insert("into", "进");
    tree3.tree_insert("dark", "良");
    tree3.tree_insert("night","夜");
    tree3.breadth_first_walk_print(true);
    tree3.pre_order_print();

    std::cout << "----------------------Testing Tree Searching----------------------" << std::endl;
    std::vector<node<std::string>*> rg_search_test = tree3.range_search("a", "d");
    for(auto i : rg_search_test){
        std::cout << i->value << " ";
    }
    std::cout << std::endl;

    std::cout << "-------------------------Testing Tree Deletion------------------" << std::endl;
    node<int>* p = nullptr;
    red_black_tree<int> tree1;
    tree1.tree_insert(8);
    tree1.tree_insert(4);
    tree1.tree_insert(10);
    tree1.tree_insert(2);
    tree1.tree_insert(6);
    tree1.tree_insert(9);
    tree1.tree_insert(12);
    tree1.tree_insert(1);
    tree1.tree_insert(3);
    tree1.tree_insert(5);
    tree1.tree_insert(7);
    tree1.tree_insert(11);
    tree1.breadth_first_walk_print();
    p = tree1.tree_search(3);
    tree1.tree_delete(p);
    tree1.breadth_first_walk_print();
    p = tree1.tree_search(2);
    tree1.tree_delete(p);
    tree1.breadth_first_walk_print();
    p = tree1.tree_search(9);
    tree1.tree_delete(p);
    tree1.breadth_first_walk_print();
    p = tree1.tree_search(4);
    tree1.tree_delete(p);
    tree1.breadth_first_walk_print();
    p = tree1.tree_search(10);
    tree1.tree_delete(p);
    tree1.breadth_first_walk_print();
    p = tree1.tree_search(11);
    tree1.tree_delete(p);
    tree1.breadth_first_walk_print();
    p = tree1.tree_search(8);
    tree1.tree_delete(p);
    tree1.breadth_first_walk_print();

    return 0;
}