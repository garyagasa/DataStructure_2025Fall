#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;

typedef struct ListNode{
    int val;
    struct ListNode* next;
}ListNode;

ListNode* mergeKLists(ListNode ** lists, int k){
    struct cmp{
        bool operator()(ListNode* a, ListNode* b){
            return a->val > b->val;
        }
    };

    // Initialize the priority queue
    priority_queue<ListNode*, vector<ListNode*>, cmp> pq;
    for(int i = 0; i < k; i++){
        pq.push(lists[i]);
    }

    ListNode* ret = nullptr;
    ListNode* tail = nullptr;

    while(!pq.empty()){
        auto p = pq.top();
        pq.pop();
        if(p->next != nullptr){
            pq.push(p->next);
        }

        if(ret == nullptr){
            ret = p;
            tail = p;
        }
        else{
            tail->next = p;
            tail = p;
        }
    }

    return ret;
}

// 辅助函数：创建链表
ListNode* createList(const std::vector<int>& vals) {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for(int v : vals) {
        ListNode* node = new ListNode{v, nullptr};
        if(!head) { head = node; tail = node; }
        else { tail->next = node; tail = node; }
    }
    return head;
}

// 辅助函数：打印链表
void printList(ListNode* head) {
    while(head) {
        std::cout << head->val;
        if(head->next) std::cout << " -> ";
        head = head->next;
    }
    std::cout << std::endl;
}

int main() {
    // 样例1：合并3个有序链表
    std::vector<int> a1 = {1,4,7};
    std::vector<int> a2 = {2,5,8};
    std::vector<int> a3 = {3,6,9};
    ListNode* lists1[3] = {createList(a1), createList(a2), createList(a3)};
    ListNode* merged1 = mergeKLists(lists1, 3);
    std::cout << "Test 1: "; printList(merged1); // 1->2->3->4->5->6->7->8->9

    // 样例2：有重复元素
    ListNode* lists4[2] = {createList({1,2,2}), createList({2,3})};
    ListNode* merged4 = mergeKLists(lists4, 2);
    std::cout << "Test 2: "; printList(merged4); // 1->2->2->2->3

    return 0;
}
