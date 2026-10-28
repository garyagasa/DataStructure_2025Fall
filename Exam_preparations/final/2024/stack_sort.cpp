#include <cstdio>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <algorithm>
#define maxLen 64

using namespace std;

void printStackOps();

int sequence[maxLen], len;  // sequence 为待排序序列，len为序列长度
stack<int> s;

// 判断序列是否可以排序
bool islegal(){
    int i, j, k;
    
    // Judge if the sequence can be sorted
    for(i = 0; i < len; i++){
        for(j = i + 1; j < len; j++){
            for(k = j + 1; k < len; k++){
                /*############ TODO ################*/
                if(sequence[i] < sequence[k] && sequence[k] < sequence[j])
                /*############ TODO ################*/
                    return false;
            }
        }
    }

    // print the "push" and "pop" operation
    printStackOps();
    return true;
}

// 输出push和pop顺序
void printStackOps() {
    /*############ TODO ################*/
    // Get the stack out order
    int out_sequence[maxLen];
    for(int i = 0; i < len; i++){
        out_sequence[i] = sequence[i];
    }   
    sort(out_sequence, out_sequence + len);

    stack<int> temp_stack;
    int in_p = 0;
    int out_p = 0;

    while(in_p < len && out_p < len){
        if(!temp_stack.empty() && out_sequence[out_p] == temp_stack.top()){
            cout << "pop" << endl;
            temp_stack.pop();
            out_p++;
        }
        else if(sequence[in_p] == out_sequence[out_p]){
            cout << "push" << endl;
            cout << "pop" << endl;
            in_p++;
            out_p++;
        }
        else if(sequence[in_p] != out_sequence[out_p]){
            cout << "push" << endl;
            temp_stack.push(sequence[in_p]);
            in_p++;
        }
    }
    if(in_p != len || out_p != len){
        throw runtime_error("the sequence cannot be sorted by the stack"); 
    }
    /*############ TODO ################*/
    }

    // 测试样例主函数
    int main() {
        // 测试1：可排序，随机序列
        int test1[] = {3, 1, 2, 4};
        len = 4;
        for(int i = 0; i < len; i++) sequence[i] = test1[i];
        cout << "Test 1: 3 1 2 4 (可排序)\n";
        if (!islegal()) cout << "No\n";
        cout << "---------------------\n";

        // 测试2：不可排序，随机序列
        int test2[] = {2, 4, 1, 3};
        len = 4;
        for(int i = 0; i < len; i++) sequence[i] = test2[i];
        cout << "Test 2: 2 4 1 3 (不可排序)\n";
        if (!islegal()) cout << "No\n";
        cout << "---------------------\n";

        // 测试3：升序
        int test3[] = {1, 2, 3, 4, 5};
        len = 5;
        for(int i = 0; i < len; i++) sequence[i] = test3[i];
        cout << "Test 3: 1 2 3 4 5 (可排序)\n";
        if (!islegal()) cout << "No\n";
        cout << "---------------------\n";

        // 测试4：降序
        int test4[] = {5, 4, 3, 2, 1};
        len = 5;
        for(int i = 0; i < len; i++) sequence[i] = test4[i];
        cout << "Test 4: 5 4 3 2 1 (可排序)\n";
        if (!islegal()) cout << "No\n";
        cout << "---------------------\n";

        // 测试5：不可排序，复杂
        int test5[] = {4, 1, 3, 2, 5};
        len = 5;
        for(int i = 0; i < len; i++) sequence[i] = test5[i];
        cout << "Test 5: 4 1 3 2 5 (不可排序)\n";
        if (!islegal()) cout << "No\n";
        cout << "---------------------\n";

        return 0;
}