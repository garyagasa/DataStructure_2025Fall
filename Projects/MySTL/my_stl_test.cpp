#include <cstdio>
#include <iostream>
#include "my_stl.h"

int main(){
    my_stack<int> s1(8);
    for(int i = 0; i < 20; i++){
        s1.push(i);
    }
    for(int i = 0; i < 20; i++){
        s1.push(-i);
    }
    for(int i = 0; i < 30; i++){
        std::cout << s1.top() << " ";
        s1.pop();
    }
    std::cout << std::endl;

    my_queue<int> q1;
    for(int i = 0; i < 40; i++){
        q1.push(i);
    }
    for(int i = 0; i < 40; i++){
        std::cout << q1.front() << " ";
        q1.pop();
    }
    std::cout << std::endl;

    my_priority_queue<int> h1(true);
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