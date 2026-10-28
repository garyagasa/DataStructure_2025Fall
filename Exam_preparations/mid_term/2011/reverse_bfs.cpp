#include<cstdio>
#include<iostream>
#include<stack>
#include<queue>

using namespace std;

struct node{
    int value;
    node* left;
    node* right;
};

void reverse_bfs(node* root){
    queue<node*> fringe;
    stack<node*> memory;

    fringe.push(root);

    while(!fringe.empty()){
        node* node_poped = fringe.front();
        fringe.pop();
        memory.push(node_poped);
        
        if(node_poped->right != nullptr){
            fringe.push(node_poped->right);
        }

        if(node_poped->left != nullptr){
            fringe.push(node_poped->left);
        }
    }

    while(!memory.empty()){
        std::cout << memory.top()->value << std::endl;
        memory.pop();
    }
}

int main() {
    node* root = new node{1, nullptr, nullptr};
    root->left = new node{2, nullptr, nullptr};
    root->right = new node{3, nullptr, nullptr};
    root->left->left = new node{4, nullptr, nullptr};
    root->left->right = new node{5, nullptr, nullptr};
    root->right->left = new node{6, nullptr, nullptr};
    root->right->right = new node{7, nullptr, nullptr};
    
    std::cout << "Reverse BFS Output:" << std::endl;
    reverse_bfs(root);

    return 0;
}