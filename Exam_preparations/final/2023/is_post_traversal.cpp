#include <cstdio>
#include <iostream>
#include <cassert>

bool helper(int* arr, int begin, int end);

bool is_post(int* arr, int num){
    return helper(arr, 0, num);
}

bool helper(int* arr, int begin, int end){
    if(end - begin < 4) return true;
    int partition = arr[end - 1];
    int new_end = begin;
    for(int i = begin; i < end; i++){
        if(arr[i] > partition){
            new_end = i;
            break;
        }
    }
    for(int i = new_end; i < end; i++){
        if(arr[i] < partition){
            return false;
        }
    }
    return helper(arr, begin, new_end) && helper(arr, new_end, end - 1);
}

int main(){
    int arr1[] = {5, 7, 6, 9, 11, 10, 8};
    assert(is_post(arr1, 7) == true);
    int arr2[] = {7, 4, 5, 6};
    assert(is_post(arr2, 4) == false);
    std::cout << "pass all tests" << std::endl;
    return 0;
}