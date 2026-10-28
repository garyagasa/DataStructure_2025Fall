#include <cstdio>
#include <iostream>
#include <cassert>

int num_f_n(int n){
    int ret_arr[n + 1];
    ret_arr[0] = 1;

    for(int i = 1; i <= n; i++){
        ret_arr[i] = i * ret_arr[i / 2];
    }

    return ret_arr[n];
}

int main(){
    std::cout << "-------------START TESTING------------------" << std::endl;
    
    // 基础情况
    assert(num_f_n(0) == 1);
    assert(num_f_n(1) == 1);
    assert(num_f_n(2) == 2);
    
    // 普通情况
    assert(num_f_n(3) == 3);
    assert(num_f_n(4) == 8);
    assert(num_f_n(5) == 10);
    
    // 较大的数
    assert(num_f_n(6) == 18);  // 6 * f(3) = 6 * 3 = 18
    assert(num_f_n(8) == 64);  // 8 * f(4) = 8 * 8 = 64
    
    std::cout << "All tests passed!" << std::endl;
    
    return 0;
}