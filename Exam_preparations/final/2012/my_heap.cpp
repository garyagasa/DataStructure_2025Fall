#include <cstdio>
#include <vector>
#include <stdexcept>
#include <iostream>
using namespace std;

class my_heap{
    private:
    vector<int> arr = vector<int>(1, 0);    // sentinel

    public:
    void push(int i){
        arr.push_back(i);
        int pos = arr.size() - 1;
        
        while(pos > 1){
            if(arr[pos] >= arr[pos / 2]){
                break;
            }
            swap(arr[pos], arr[pos / 2]);
            pos /= 2;
        }
    }

    int pop(){
        int ret = arr[1];
        arr[1] = arr[arr.size() - 1];
        arr.pop_back();

        int pos = 1;
        while(pos <= (arr.size() - 1) / 2){
            int left_child = 2 * pos;
            int right_child = 2 * pos + 1;

            // consider out of boundary case
            if((right_child == arr.size() && arr[pos] <= arr[left_child]) ||
                (arr[pos] <= arr[left_child] && arr[pos] <= arr[right_child])){
                break;        
            }

            if(right_child == arr.size() || (arr[left_child] < arr[right_child])){
                swap(arr[pos], arr[left_child]);
                pos = left_child;
            }
            else{
                swap(arr[pos], arr[right_child]);
                pos = right_child;
            }
        }

        return ret;
    }
};