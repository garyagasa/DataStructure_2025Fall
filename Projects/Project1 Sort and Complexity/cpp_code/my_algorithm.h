// my_algorithm.h
#pragma once
#include <vector>
#include <cmath>

// 示例算法：计算向量元素的平方和
double compute_square_sum(const std::vector<double>& data) {
    double sum = 0.0;
    for (const auto& value : data) {
        sum += value * value;
    }
    return sum;
}

// 另一个示例算法：冒泡排序
void bubble_sort(std::vector<int>& data) {
    int n = data.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (data[j] > data[j+1]) {
                std::swap(data[j], data[j+1]);
            }
        }
    }
}