// benchmark.cpp
#include "my_algorithm.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>

// 生成随机向量
std::vector<double> generate_random_vector(size_t size, double min = 0.0, double max = 1.0) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    
    std::vector<double> result(size);
    for (size_t i = 0; i < size; ++i) {
        result[i] = dis(gen);
    }
    return result;
}

// 测量执行时间
template<typename Func, typename... Args>
long long measure_time(Func func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    func(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main() {
    // 测试不同输入大小的执行时间
    std::ofstream outfile("../data/results.csv");
    outfile << "algorithm,parameter,time_us\n";
    
    int low_bound = 100;
    int up_bound = 10000;
    int step = 100;
    // 测试bubble_sort在不同输入大小下的性能
    // for (size_t size = low_bound; size <= up_bound; size += step) {
    //     auto data = generate_random_vector(size);
    //     std::vector<int> int_data(data.begin(), data.end());
        
    //     long long time_taken = measure_time(bubble_sort, int_data);
        
    //     outfile << "bubble_sort," << size << "," << time_taken << "\n";
    // }

    // 测试Insertion_sort在不同输入大小下的性能
    for (size_t size = low_bound; size <= up_bound; size += step) {
        auto data = generate_random_vector(size);
        std::vector<int> int_data(data.begin(), data.end());
        
        long long time_taken = measure_time(Insertion_sort, int_data);
        
        outfile << "Insertion_sort," << size << "," << time_taken << "\n";
    }

    // 测试Merge_sort在不同输入大小下的性能
    for (size_t size = low_bound; size <= up_bound; size += step) {
        auto data = generate_random_vector(size);
        std::vector<int> int_data(data.begin(), data.end());
        
        long long time_taken = measure_time(Merge_sort, int_data);
        
        outfile << "Merge_sort," << size << "," << time_taken << "\n";
    }
    
    outfile.close();
    return 0;
}