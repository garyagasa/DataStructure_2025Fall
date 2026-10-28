#include "my_heap.h"
#include <iostream>
#include <cstdio>

int main(){
    my_heap<int> h1(true);
    for(int i = 4; i < 10; i++){
        h1.push(i);
    }

    for(int i = 0; i < 4; i++){
        std::cout << h1.top() << " ";
        h1.pop();
    }
    std::cout << std::endl;
    return 0;
}