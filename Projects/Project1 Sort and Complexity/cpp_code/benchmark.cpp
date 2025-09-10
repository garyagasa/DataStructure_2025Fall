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
    
    int low_bound = 10;
    int up_bound = 700;
    int step = 1;
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

//    // 测试 Merge_sort
//     for (size_t size = low_bound; size <= up_bound; size += step) {
//         long long avgtime = 0;
//         for(int time = 0; time < repeat_time; time++){
//             auto data = generate_random_vector(size);
//             long long time_taken = measure_time(Merge_sort_1<int>, data);
//             avgtime += time_taken;
//         }
//         avgtime /= repeat_time;
//         outfile << "Merge_sort," << size << "," << avgtime << "\n";
//     }

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
            long long time_taken = measure_time(Improved_Sort<int>, data);
            avgtime += time_taken;
        }
        avgtime /= repeat_time;
        outfile << "Improved_sort," << size << "," << avgtime << "\n";
    }

    outfile.close();
    return 0;
}
