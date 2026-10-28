#include <cstdio>
#include <iostream>
using namespace std;

int search(int data[], int left, int right, int n){
    int low = left, up = right, tmp;
    while(low <= up){
        tmp = (low + up) / 2;
        if(data[tmp] == n) return tmp;
        if(data[tmp] < n) low = tmp + 1;
        else up = tmp - 1;
    }
    return -1;
}

int search_improve(int data[], int left, int right, int n){
    int low = left, up = right, tmp;
    while(low <= up){
        tmp = (low + up) / 2;
        if(data[tmp] < n) low = tmp + 1;


        
        else if(data[tmp] > n) up = tmp - 1;
        else{
            if(data[left] == n) return left;
            else left += 1;
        }
    }
    return -1;
}

int main() {
    int arr1[] = {1, 3, 5, 5, 5, 5, 5, 5, 7, 9, 11, 13};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    // 1. 查找存在的元素
    cout << "search(arr1, 0, n1-1, 7): " << search(arr1, 0, n1-1, 7) << endl;    // 3
    cout << "search(arr1, 0, n1-1, 1): " << search(arr1, 0, n1-1, 1) << endl;    // 0
    cout << "search(arr1, 0, n1-1, 5): " << search(arr1, 0, n1-1, 5) << endl; 

    // 2. 查找不存在的元素
    cout << "search(arr1, 0, n1-1, 2): " << search(arr1, 0, n1-1, 2) << endl;    // -1
    cout << "search(arr1, 0, n1-1, 0): " << search(arr1, 0, n1-1, 0) << endl;    // -1
    cout << "search(arr1, 0, n1-1, 20): " << search(arr1, 0, n1-1, 20) << endl;  // -1

    // 3. 空数组
    int arr2[] = {};
    cout << "search(arr2, 0, -1, 5): " << search(arr2, 0, -1, 5) << endl;        // -1

    // 4. 单元素数组
    int arr3[] = {8};
    cout << "search(arr3, 0, 0, 8): " << search(arr3, 0, 0, 8) << endl;          // 0
    cout << "search(arr3, 0, 0, 3): " << search(arr3, 0, 0, 3) << endl;          // -1

    // 对 search_improve 也做同样测试
    cout << "search_improve(arr1, 0, n1-1, 7): " << search_improve(arr1, 0, n1-1, 7) << endl;
    cout << "search_improve(arr1, 0, n1-1, 1): " << search_improve(arr1, 0, n1-1, 1) << endl;
    cout << "search_improve(arr1, 0, n1-1, 5): " << search_improve(arr1, 0, n1-1, 5) << endl;
    cout << "search_improve(arr1, 0, n1-1, 2): " << search_improve(arr1, 0, n1-1, 2) << endl;
    cout << "search_improve(arr2, 0, -1, 5): " << search_improve(arr2, 0, -1, 5) << endl;
    cout << "search_improve(arr3, 0, 0, 8): " << search_improve(arr3, 0, 0, 8) << endl;
    cout << "search_improve(arr3, 0, 0, 3): " << search_improve(arr3, 0, 0, 3) << endl;

    return 0;
}