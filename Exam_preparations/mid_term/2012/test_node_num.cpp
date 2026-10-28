#include <cstdio>
#include <iostream>
#include <functional>
#include "node_num.cpp"

// --- Test Code ---

BiTNode* createNode(int val) {
    BiTNode* node = new BiTNode;
    node->data = val;
    node->LChild = NULL;
    node->RChild = NULL;
    return node;
}

void destroyTree(BiTree root) {
    if (root) {
        destroyTree(root->LChild);
        destroyTree(root->RChild);
        delete root;
    }
}

int main() {
    std::cout << "Running Test Cases for leave_node_num..." << std::endl;

    // Test Case 1: Empty Tree
    std::cout << "Test Case 1 (Empty Tree): ";
    if (leave_node_num(NULL) == 0) std::cout << "PASS" << std::endl;
    else std::cout << "FAIL (Expected 0)" << std::endl;

    // Test Case 2: Single Node
    BiTree t2 = createNode(1);
    std::cout << "Test Case 2 (Single Node): ";
    if (leave_node_num(t2) == 1) std::cout << "PASS" << std::endl;
    else std::cout << "FAIL (Expected 1, Got " << leave_node_num(t2) << ")" << std::endl;
    destroyTree(t2);

    // Test Case 3: Left Child only (1 -> 2)
    BiTree t3 = createNode(1);
    t3->LChild = createNode(2);
    std::cout << "Test Case 3 (Left Child Only): ";
    if (leave_node_num(t3) == 1) std::cout << "PASS" << std::endl;
    else std::cout << "FAIL (Expected 1, Got " << leave_node_num(t3) << ")" << std::endl;
    destroyTree(t3);

    // Test Case 4: Right Child only (1 -> 3)
    BiTree t4 = createNode(1);
    t4->RChild = createNode(3);
    std::cout << "Test Case 4 (Right Child Only): ";
    if (leave_node_num(t4) == 1) std::cout << "PASS" << std::endl;
    else std::cout << "FAIL (Expected 1, Got " << leave_node_num(t4) << ")" << std::endl;
    destroyTree(t4);

    // Test Case 5: Both Children (1 -> 2, 3) - This is where the bug will show
    BiTree t5 = createNode(1);
    t5->LChild = createNode(2);
    t5->RChild = createNode(3);
    std::cout << "Test Case 5 (Both Children): ";
    int res5 = leave_node_num(t5);
    if (res5 == 2) std::cout << "PASS" << std::endl;
    else std::cout << "FAIL (Expected 2, Got " << res5 << ") - Note: Code has logic error in branching" << std::endl;
    destroyTree(t5);

    // Test Case 6: Complex Tree
    //      1
    //     / \
    //    2   3
    //   / \
    //  4   5
    BiTree t6 = createNode(1);
    t6->LChild = createNode(2);
    t6->RChild = createNode(3);
    t6->LChild->LChild = createNode(4);
    t6->LChild->RChild = createNode(5);
    std::cout << "Test Case 6 (Complex Tree): ";
    int res6 = leave_node_num(t6);
    if (res6 == 3) std::cout << "PASS" << std::endl;
    else std::cout << "FAIL (Expected 3, Got " << res6 << ")" << std::endl;
    destroyTree(t6);

    return 0;
}
