#include <cstdio>
#include <iostream>

int nearest_common_ancestor(int a, int b){
    int a_ptr = a;
    int b_ptr = b;

    while(a_ptr != b_ptr){
        if(a_ptr > b_ptr){
            a_ptr /= 2;
        }
        else{
            b_ptr /= 2;
        }
    }

    return a_ptr;
}

int main(){
    std::cout << nearest_common_ancestor(7, 12) << std::endl;
    return 0;
}