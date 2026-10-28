#include <cstdio>
#include <iostream>

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x): val(x), left(nullptr), right(nullptr){};
};

int CountNodes(TreeNode* root){
    if(root == nullptr){
        return 0;
    }
    return 1 + CountNodes(root->left) + CountNodes(root->right);
}

int main() {
    // 样例1：空树
    TreeNode* root1 = nullptr;
    std::cout << "Test 1 (空树): " << CountNodes(root1) << std::endl; // 0

    // 样例2：单节点树
    TreeNode* root2 = new TreeNode(1);
    std::cout << "Test 2 (单节点): " << CountNodes(root2) << std::endl; // 1

    // 样例3：完全二叉树
    TreeNode* root3 = new TreeNode(1);
    root3->left = new TreeNode(2);
    root3->right = new TreeNode(3);
    root3->left->left = new TreeNode(4);
    root3->left->right = new TreeNode(5);
    root3->right->left = new TreeNode(6);
    root3->right->right = new TreeNode(7);
    std::cout << "Test 3 (完全二叉树): " << CountNodes(root3) << std::endl; // 7

    // 样例4：不完全二叉树
    TreeNode* root4 = new TreeNode(1);
    root4->left = new TreeNode(2);
    root4->right = new TreeNode(3);
    root4->left->right = new TreeNode(4);
    std::cout << "Test 4 (不完全二叉树): " << CountNodes(root4) << std::endl; // 4

    // 样例5：只有左子树
    TreeNode* root5 = new TreeNode(1);
    root5->left = new TreeNode(2);
    root5->left->left = new TreeNode(3);
    std::cout << "Test 5 (只有左子树): " << CountNodes(root5) << std::endl; // 3

    return 0;
}