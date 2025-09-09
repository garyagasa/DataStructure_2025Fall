// my_algorithm.h
#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>

template<typename T>
void bubble_sort(std::vector<T>& data) {
    int n = data.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (data[j] > data[j+1]) {
                std::swap(data[j], data[j+1]);
            }
        }
    }
}

// Question1: Insertion Sort
template<typename T>
void Insertion_sort(std::vector<T>& arr){
    int length = arr.size();
    for(int j = 1; j < length; j++){
        T key = arr[j];
        int i = j - 1;
        while(i >= 0 && arr[i] > key){
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i + 1] = key;
    }
}

// Question2: Merge Sort
template<typename T>
void Merge_sort(std::vector<T>& arr){
    std::function<void(int, int)> helper = [&](int left, int right) -> void{
        if(left >= right - 1){
            return;
        }
        
        std::vector<T> temp(arr.size()); // temporary vector to store the element

        int middle = (left + right) / 2;
        // devide
        helper(left, middle);
        helper(middle, right);
        
        for(int i = left; i < right; i++){
            temp[i] = arr[i];
        }
        
        // conquer
        int p1 = 0, p2 = 0, p = left;
        while(p1 < middle - left || p2 < right - middle){
            // left used up
            if(p1 == middle - left){
                arr[p] = temp[p2 + middle];
                p2++;
            }
            // right used up
            else if(p2 == right - middle){
                arr[p] = temp[p1 + left];
                p1++;
            }
            // both not used up
            else if(temp[p1 + left] < temp[p2 + middle]){
                arr[p] = temp[p1 + left];
                p1++;
            }
            else{
                arr[p] = temp[p2 + middle];
                p2++; 
            }
            p++;   
        }
    };
    helper(0, arr.size());
}

// Question3: Quick Sort
template<typename T>
void Quick_sort_naive(std::vector<T>& arr){

    std::function<void(int, int)> helper = [&](int left, int right) -> void{
        // right is exclusive
        if(left >= right - 1){
            return;
        }

        // partition, choose arr[left] to be the pivot
        T pivot = arr[left];
        int last_p = right- 1;
        for(int i = left + 1; i < last_p; i++){
            if(arr[i] > pivot){
                std::swap(arr[i], arr[last_p]);
                last_p--;
            }
        }
        std::swap(arr[left], arr[last_p]);

        helper(left, last_p);
        helper(last_p + 1, right);
    };
    
    helper(0, arr.size());
}

// Question4: Improved Sort
template<typename T>
void Improved_Sort(std::vector<T>& arr, int k){
// To-Do: Implement the algorithm combining the quick sort and insertion sort
}