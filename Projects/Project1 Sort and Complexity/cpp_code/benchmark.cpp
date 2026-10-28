// benchmark.cpp
#include "my_algorithm.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>

// 生成随机整数向量
std::vector<int> generate_random_vector(size_t size, int min = 0, int max = 100000) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    
    std::vector<int> result(size);
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
    // 输出到 CSV 文件
    std::ofstream outfile("../data/results.csv");
    outfile << "algorithm,parameter,time_us\n";
    
    int low_bound = 10000;
    int up_bound = 50000;
    int step = 1000;
    int repeat_time = 10;

    // 测试 Insertion_sort
    for (size_t size = low_bound; size <= up_bound; size += step) {
        long long avgtime = 0;
        for(int time = 0; time < repeat_time; time++){
            auto data = generate_random_vector(size);
            long long time_taken = measure_time(Insertion_sort<int>, data);
            avgtime += time_taken;
        }
        avgtime /= repeat_time;
        outfile << "Insertion_sort," << size << "," << avgtime << "\n";
    }

   // 测试 Merge_sort
    for (size_t size = low_bound; size <= up_bound; size += step) {
        long long avgtime = 0;
        for(int time = 0; time < repeat_time; time++){
            auto data = generate_random_vector(size);
            long long time_taken = measure_time(Merge_sort_1<int>, data);
            avgtime += time_taken;
        }
        avgtime /= repeat_time;
        outfile << "Merge_sort," << size << "," << avgtime << "\n";
    }

    // 测试 Quick_sort
    for (size_t size = low_bound; size <= up_bound; size += step) {
        long long avgtime = 0;
        for(int time = 0; time < repeat_time; time++){
            auto data = generate_random_vector(size);
            long long time_taken = measure_time(Quick_sort_naive<int>, data);
            avgtime += time_taken;
        }
        avgtime /= repeat_time;
        outfile << "Quick_sort," << size << "," << avgtime << "\n";
    }
    
    // 测试 Improved_sort
    for (size_t size = low_bound; size <= up_bound; size += step) {
        long long avgtime = 0;
        for(int time = 0; time < repeat_time; time++){
            auto data = generate_random_vector(size);
            long long time_taken = measure_time(Improved_Sort_k<int>, data, 120);
            avgtime += time_taken;
        }
        avgtime /= repeat_time;
        outfile << "Improved_sort," << size << "," << avgtime << "\n";
    }

    outfile.close();

    // To-Do: Test Improved sort on different values of k, output to the file "qs_results.csv" 
    std::ofstream outfile1("../data/qs_results.csv");
    outfile1 << "k_num,time_us\n";
    int k_low = 0;
    int k_high = 600;
    int k_step = 2;
    int repeat_time1 = 20;
    int size = 50000;

    for(int k = k_low; k < k_high; k += k_step){
        long long avgtime = 0;
        for(int time = 0; time < repeat_time1; time++){
            auto data = generate_random_vector(size);
            long long time_taken = measure_time(Improved_Sort_k<int>, data, k);
            avgtime += time_taken;
        }
        avgtime /= repeat_time1;
        outfile1 << k << "," << avgtime << "\n";
    }
    outfile1.close();

    return 0;
}
