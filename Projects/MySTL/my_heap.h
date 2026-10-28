#pragma once
#include <cstdio>
#include <stdexcept>

template <typename T>
class my_heap{
    private:
    T* CBT;         // Complete Binary Tree to build the heap, the first element is at index 1
    int max_num;    // size of the array
    int num;        // current number of the elements in the array
    bool max_heap;

    // return the parent of the index
    int parent(int index){
        if(index == 0){
            throw std::invalid_argument("root has no parent");
        }
        return index / 2;
    }

    // return the left child of the index
    int left_child(int index){
        return 2 * index;
    }

    // return the right child of the index
    int right_child(int index){
        return 2 * index + 1;
    }

    int greater_child(int index){
        if(index > parent(num)){
            throw std::invalid_argument("leaf node, no child");
        }
        // no right child
        if(right_child(index) > num){
            return left_child(index);
        }
        if(more_prior(CBT[right_child(index)], CBT[left_child(index)])){
            return right_child(index);
        }
        return left_child(index);
    }

    bool is_full(){
        return 1 + num >= max_num;
    }

    // return if t1 should be more prior than t2 in the heap
    bool more_prior(T t1, T t2){
        if(max_heap){
            return t1 > t2;
        }
        else{
            return t1 < t2;
        }
    }

    void swap(int index1, int index2){
        if(index1 > max_num || index2 > max_num){
            throw std::out_of_range("index is bigger than max_num of the heap"); 
        }
        T temp = CBT[index1];
        CBT[index1] = CBT[index2];
        CBT[index2] = temp;
    }

    // change the value at some "index" to value_changed, then changes its position
    void adjust_pos(int index, T value_changed){
        CBT[index] = value_changed;
        int ptr = index;
        if(index != 1 && more_prior(CBT[index], CBT[parent(index)])){    // not root
            while(ptr != 1 && more_prior(CBT[ptr], CBT[parent(ptr)])){
                swap(ptr, parent(ptr));
                ptr = parent(ptr);
            }
        }

        if(index <= parent(num) && more_prior(CBT[greater_child(index)], CBT[index])){
            while(ptr <= parent(num) && (more_prior(CBT[greater_child(ptr)], CBT[ptr]))){     // not leaf node
                swap(ptr, greater_child(ptr));
                ptr = greater_child(ptr);
            }       
        }
    }

    public:
    // Constructor
    // CBT is a Complete Binary Tree array, indexed from 1 (CBT[1] is the first element)
    my_heap(bool is_max_heap=true, int number=64){
        CBT = (T*)malloc(number * sizeof(T));
        num = 0;
        max_num = number;
        max_heap = is_max_heap;
    }

    // empty method
    bool empty(){
        return (num == 0);
    }
    // Push method
    void push(T element){
        if(is_full()){
            T* new_arr = (T*)malloc(max_num * sizeof(T) * 2);
            for(int i = 1; i < max_num; i++){
                new_arr[i] = CBT[i];
            }
            max_num *= 2;
            free(CBT);
            CBT = new_arr;
        }
        // Insert to the tail first
        num++;
        adjust_pos(num, element);
    }
    // Pop method
    void pop(){
        if(empty()){
            throw std::invalid_argument("the heap is empty");
        }
        num--;
        adjust_pos(1, CBT[num + 1]);
    }
    // Top method
    T top(){
        if(empty()){
            throw std::invalid_argument("the heap is empty");
        }
        return CBT[1];
    }
};