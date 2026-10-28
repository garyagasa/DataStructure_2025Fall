#include "my_heap.cpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // 基本功能测试
    my_heap h;
    vector<int> test_data = {5, 3, 8, 1, 6, 9, 2};
    cout << "[样例1] 插入元素: ";
    for (int x : test_data) {
        cout << x << " ";
        h.push(x);
    }
    cout << endl << "[样例1] 依次弹出元素: ";
    for (size_t i = 0; i < test_data.size(); ++i) {
        cout << h.pop() << " ";
    }
    cout << endl;

    // 重复元素测试
    my_heap h2;
    vector<int> test_data2 = {4, 4, 4, 4};
    cout << "[样例2] 插入重复元素: ";
    for (int x : test_data2) {
        cout << x << " ";
        h2.push(x);
    }
    cout << endl << "[样例2] 依次弹出元素: ";
    for (size_t i = 0; i < test_data2.size(); ++i) {
        cout << h2.pop() << " ";
    }
    cout << endl;

    // 负数和零测试
    my_heap h3;
    vector<int> test_data3 = {0, -1, -5, 3, 2};
    cout << "[样例3] 插入负数和零: ";
    for (int x : test_data3) {
        cout << x << " ";
        h3.push(x);
    }
    cout << endl << "[样例3] 依次弹出元素: ";
    for (size_t i = 0; i < test_data3.size(); ++i) {
        cout << h3.pop() << " ";
    }
    cout << endl;

    // 单元素测试
    my_heap h4;
    cout << "[样例4] 插入单个元素: 42\n";
    h4.push(42);
    cout << "[样例4] 弹出: " << h4.pop() << endl;

    return 0;
}
