#include <cstdio>
#include <iostream>
#include <functional>

typedef int DataType;

typedef struct BiTNode{
    DataType data;
    struct BiTNode *LChild, *RChild;
}BiTNode, *BiTree;

int leave_node_num(BiTree root){
    if(root == NULL) return 0;
    int num = 0;

    std::function<void(BiTNode*)> DFS = [&](BiTNode* node_ptr) -> void{
        if(node_ptr->LChild == NULL && node_ptr->RChild == NULL){
            num++;
            return;
        }
        if(node_ptr->LChild != NULL){
            DFS(node_ptr->LChild);
        }
        if(node_ptr->RChild != NULL){
            DFS(node_ptr->RChild);
        }
    };
    DFS(root);
    return num;
}