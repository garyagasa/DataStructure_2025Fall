#include "../io.h"
#include "../bst/red_black.h"
using namespace std;

int main(){
    red_black_tree<string> rb1;
    vector<pair<string, string>> df1 = read_txt_double("../data/init.txt");
    vector<string> df2 = read_txt_single("../data/delete.txt");
    // Initialize test
    for(auto [english, chinese] : df1){
        rb1.tree_insert(english, chinese);
    }
    // rb1.breadth_first_walk_print(true);

    // Query test(Success)
    string english1 = "autofill";
    node<string>* p1 = rb1.tree_search(english1);
    if(p1 == nullptr){
        std::cout << "404 not found" << std::endl;
    }
    else{
        std::cout << english1 << "的意思是: " << p1->satellite << std::endl; 
    }

    // Query test(Fail)
    string english2 = "aoligei";
    node<string>* p2 = rb1.tree_search(english2);
    if(p2 == nullptr){
        std::cout << "404 not found" << std::endl;
    }
    else{
        std::cout << english2 << "的意思是: " << p2->satellite << std::endl; 
    } 
    
    // Query and delete test
    std::cout << "Query and delete test"<< std::endl;
    for(auto english : df2){
        node<string>* p = rb1.tree_search(english);
        std::cout << english << "的意思是: " << p->satellite << std::endl; 
        rb1.tree_delete(p);
    }

    // Range search test
    std::vector<node<std::string>*> rg_search_test = rb1.range_search("android", "apple");
    for(auto i : rg_search_test){
        std::cout << i->value << " ";
    }
    std::cout << std::endl;
}