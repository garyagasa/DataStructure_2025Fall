#include <cstdio>
#include <iostream>
#include <stack>
#include <queue>
#include <cassert>

typedef struct LNode{
    int data;
    struct LNode* link;
} LNode;

bool balance(LNode* list){
    LNode* p_1 = list;
    LNode* p_2 = list;

    /* Judge the middle point of the list */
    while(p_2->link != NULL && p_2->link->link != NULL){
        p_1 = p_1->link;
        p_2 = p_2->link->link;
    }

    bool result = true;

    // Case 1: Odd Nodes, Even Edges
    if(p_2->link == NULL){
        LNode* p1 = list;
        LNode* p2 = p_1->link;

        std::queue<int> queue_p1;
        std::stack<int> stack_p2;
        while(p1 != p_1 && p2 != NULL){
            queue_p1.push(p1->data);
            stack_p2.push(p2->data);
            p1 = p1->link;
            p2 = p2->link;
        }

        // Pop the queue and stack
        while((!queue_p1.empty()) && (!stack_p2.empty())){
            int num1 = queue_p1.front();
            int num2 = stack_p2.top();
            if(num1 != num2){
                result = false;
                break;
            }
            queue_p1.pop();
            stack_p2.pop();
        }
    }
    // Case 2: Odd Edges, Even Nodes
    else{
        LNode* p1 = list;
        LNode* p2 = p_1->link;

        std::queue<int> queue_p1;
        std::stack<int> stack_p2;
        while(p1 != p_1->link && p2 != NULL){
            queue_p1.push(p1->data);
            stack_p2.push(p2->data);
            p1 = p1->link;
            p2 = p2->link;
        }

        // Pop the queue and stack
        while((!queue_p1.empty()) && (!stack_p2.empty())){
            int num1 = queue_p1.front();
            int num2 = stack_p2.top();
            if(num1 != num2){
                result = false;
                break;
            }
            queue_p1.pop();
            stack_p2.pop();
        }
    }

    return result;
}

// 辅助函数：创建链表
LNode* createList(int arr[], int size){
    if(size == 0) return NULL;
    LNode* head = new LNode{arr[0], NULL};
    LNode* p = head;
    for(int i = 1; i < size; i++){
        p->link = new LNode{arr[i], NULL};
        p = p->link;
    }
    return head;
}

// 辅助函数：释放链表
void deleteList(LNode* head){
    while(head != NULL){
        LNode* temp = head;
        head = head->link;
        delete temp;
    }
}

int main(){
    std::cout << "-------------START TESTING------------------" << std::endl;
    
    // 测试1：奇数个节点，回文
    int arr1[] = {1, 2, 3, 2, 1};
    LNode* list1 = createList(arr1, 5);
    assert(balance(list1) == true);
    deleteList(list1);
    
    // 测试2：奇数个节点，非回文
    int arr2[] = {1, 2, 3, 4, 5};
    LNode* list2 = createList(arr2, 5);
    assert(balance(list2) == false);
    deleteList(list2);
    
    // 测试3：偶数个节点，回文
    int arr3[] = {1, 2, 2, 1};
    LNode* list3 = createList(arr3, 4);
    assert(balance(list3) == true);
    deleteList(list3);
    
    // 测试4：偶数个节点，非回文
    int arr4[] = {1, 2, 3, 4};
    LNode* list4 = createList(arr4, 4);
    assert(balance(list4) == false);
    deleteList(list4);
    
    // 测试5：单个节点
    int arr5[] = {5};
    LNode* list5 = createList(arr5, 1);
    assert(balance(list5) == true);
    deleteList(list5);
    
    // 测试6：两个相同节点
    int arr6[] = {3, 3};
    LNode* list6 = createList(arr6, 2);
    assert(balance(list6) == true);
    deleteList(list6);
    
    // 测试7：两个不同节点
    int arr7[] = {1, 2};
    LNode* list7 = createList(arr7, 2);
    assert(balance(list7) == false);
    deleteList(list7);
    
    std::cout << "All tests passed!" << std::endl;
    
    return 0;
}