#include <cstdio>
#include <vector>
#include <iostream>
#include <cassert>

int max_sub_arr(std::vector<int> arr){
    int length = arr.size();
    int max_sum = INT_MIN;
    int sum_current = 0;

    for(int i = 0; i < length; i++){
        sum_current += arr[i];
        sum_current = std::max(sum_current, 0);
        max_sum = std::max(max_sum, sum_current);
    }

    return max_sum;
}

int main(){
    std::cout << "-------------START TESTING------------------" << std::endl;
    
    // 基础情况：单个元素
    assert(max_sub_arr({5}) == 5);
    assert(max_sub_arr({-5}) == 0);
    
    // 全正数
    assert(max_sub_arr({1, 2, 3, 4, 5}) == 15);
    
    // 全负数
    assert(max_sub_arr({-1, -2, -3}) == 0);
    
    // 混合情况
    assert(max_sub_arr({-2, 1, -3, 4, -1, 2, 1, -5, 4}) == 6);  // [4, -1, 2, 1]
    assert(max_sub_arr({5, -3, 5}) == 7);  // [5, -3, 5]
    assert(max_sub_arr({-1, -2, -3, -4}) == 0);
    
    // 包含零
    assert(max_sub_arr({0, -1, 0, 2}) == 2);
    assert(max_sub_arr({-1, 0, -1}) == 0);
    
    // 大数值
    assert(max_sub_arr({100, -50, 100}) == 150);
    
    std::cout << "All tests passed!" << std::endl;
    
    return 0;
}