#include <iostream>
#include "my_algorithm.h"
#include <vector>
#include <fstream>
#include <functional>
using namespace std;

template<typename T>
void printVector(const std::vector<T>& vec, const std::string& name) {
    std::cout << name << ": ";
    for (const auto& item : vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

int main(){
    std::vector<int> arr1({1, 3, 9, 2, 5, 4, 0, 8, 7, 5, 2});
    Merge_sort(arr1);
    printVector(arr1, "Merge_sort Int");

    std::vector<int> arr1_1({1, 3, 9, 2, 5, 4, 0, 8, 7, 5, 2});
    Merge_sort(arr1_1);
    printVector(arr1_1, "Quick_sort Int");

    std::vector<float> arr2({1.2, 3.1, 9.1, 2.0, 2.5, 0.4, 3.0, 3.3, 1.7, 6.5, 8.2});
    Merge_sort(arr2);
    printVector(arr2, "Merge_sort Float");

    std::vector<float> arr2_1({1.2, 3.1, 9.1, 2.0, 2.5, 0.4, 3.0, 3.3, 1.7, 6.5, 8.2});
    Merge_sort(arr2_1);
    printVector(arr2_1, "Quick_sort Float");

    std::vector<char> arr3({'F', 'a', 'K', 'J', 'T', 'f', 'U', '_', '$', 'A', 's', 'b'});
    Merge_sort(arr3);
    printVector(arr3, "Merge_sort Char");

    std::vector<char> arr3_1({'F', 'a', 'K', 'J', 'T', 'f', 'U', '_', '$', 'A', 's', 'b'});
    Merge_sort(arr3_1);
    printVector(arr3_1, "Quick_sort Char");
    return 0;
}
