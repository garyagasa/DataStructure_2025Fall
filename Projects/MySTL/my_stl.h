#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include "my_heap.h"

template<typename T>
class my_stack{
private:
    int max_num;
    int stack_pointer;
    T* stack_arr;
public:    
    // Constructor
    my_stack(int num=16){
        stack_pointer = 0;
        max_num = num;
        stack_arr = (T*)malloc(max_num * sizeof(T));
        if(stack_arr == NULL){
            throw std::runtime_error("fail in malloc");
        }
    }
     
    // Push Method
    void push(T element){
        if(stack_pointer >= max_num){
            // Copy the old array into a bigger one
            T* new_arr = (T*)malloc(max_num * 2 *sizeof(T));
            for(int i = 0; i < max_num; i++){
                new_arr[i] = stack_arr[i];
            }
            free(stack_arr);
            stack_arr = new_arr;
            max_num *= 2;
        }
        stack_arr[stack_pointer] = element;
        stack_pointer++; 
    }
     
    // Pop Method
    void pop(){
        if(empty()){
            throw std::out_of_range("stack downflow");
            return;
        }
        stack_pointer--;
    }

    // Top method
    T top(){
        if(empty()){
            throw std::out_of_range("stack downflow");
            return NULL;
        }
        return stack_arr[stack_pointer - 1];
    }

    // empty method
    bool empty(){
        return (stack_pointer == 0);
    }

    int size(){
        return stack_pointer;
    }
};

template<typename T>
class my_queue{
private:
    int max_num;
    int head;
    int tail;
    T* queue_arr;
         
    // index up
    int index_up(int index){
        return index < max_num - 1 ? index + 1 : 0;
    }
public:    
    //Constructor
    my_queue(int num=16){
        head = 0;
        tail = 0;
        max_num = num;
        queue_arr = (T*)malloc(max_num * sizeof(T));
    }

    bool empty(){
        return (head == tail);
    }

    // Enqueue Method
    void push(T element){
        if(index_up(tail) == head){
            T* new_arr = (T*)malloc(max_num * sizeof(T) * 2);
            // the front part
            for(int i = 0; i < tail; i++){
                new_arr[i] = queue_arr[i];
            }
            // the tail part
            if(head != 0){
                for(int i = head; i < max_num; i++){
                    new_arr[i + max_num] = queue_arr[i];
                }
                head += max_num;
            }
            free(queue_arr);
            queue_arr = new_arr;
            max_num *= 2;
        }
        queue_arr[tail] = element;
        tail = index_up(tail); 
     }
     
    // Deque Method
    void pop(){
        if(empty()){
            throw std::out_of_range("queue underflow");
            return;
        }
        head = index_up(head);
    }

    T front(){
        if(empty()){
            throw std::out_of_range("empty queue");
            return NULL;
        }
        return queue_arr[head];
    }

    T back(){
        if(empty()){
            throw std::out_of_range("empty queue");
            return NULL;
        }
        return queue_arr[tail];
    }
};

template <typename T>
class my_priority_queue{
    private:
    my_heap<T> h;
    public:
    // Constructor
    my_priority_queue(bool max_priority=true, int num=64){
        h = my_heap<T>(max_priority, num);
    }
    // empty method
    bool empty(){
        return h.empty();
    }
    // Push method
    void push(T element){
        h.push(element);
    }
    // Pop method
    void pop(){
        h.pop();
    }
    // Top method
    T top(){
        return h.top();
    }
};