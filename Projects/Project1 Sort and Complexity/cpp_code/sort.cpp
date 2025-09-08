#include <iostream>
#include <vector>
#include <fstream>
#include <functional>
using namespace std;

void Insertion_sort(std::vector<int>& arr){
    int length = arr.size();
    for(int j = 2; j < length; j++){
        int key = arr[j];
        int i = j - 1;
        while(i >= 0 && arr[i] > key){
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i + 1] = key;
    }
}

void Merge_sort(std::vector<int>& arr){
    std::function<void(int, int)> helper = [&](int left, int right) -> void{
        if(left == right - 1 || left == right){
            return;
        }
        
        std::vector<int> temp(arr.size()); // temporary vector to store the element

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

int main(){
    std::vector<int> arr({1, 3, 9, 2, 5, 4});
    Merge_sort(arr);
    for(int i : arr){
        std::cout << i;
    }
    std::cout << std::endl;
    return 0;
}
