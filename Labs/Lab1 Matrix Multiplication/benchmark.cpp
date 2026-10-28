// benchmark.cpp
#include "matmul.h"
#include "matmul_pro.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>

// Generate random integer matrix
std::vector<vector<int>> generate_random_matrix(size_t n_row, size_t n_col, int min = -50000, int max = 50000) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    
    std::vector<vector<int>> result(n_row, vector<int>(n_col));
    
    for (size_t i = 0; i < n_row; i++){
        for (size_t j = 0; j < n_col; j++) {
            result[i][j] = dis(gen);
    }
    }
    return result;
}

// Measure operation time
template<typename Func, typename... Args>
long long measure_time(Func func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    func(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main() {
    // Output to the csv file "result.csv"
    std::ofstream outfile("./data/results.csv");
    outfile << "algorithm,n,time_us\n";
    
    int low_bound = 16;
    int up_bound = 512;
    int step = 16;
    int repeat_time = 40;

    // matmul_bruteforce
    for(size_t i = low_bound; i <= up_bound; i += step){
        long long avgtime = 0;
        int size = i;
        for(int time = 0; time < repeat_time; time++){
            auto m1 = generate_random_matrix(size, size);
            auto m2 = generate_random_matrix(size, size);
            long long time_taken = measure_time(matmul_bruteforce, m1, m2);
            avgtime += time_taken;
        }
        avgtime /= repeat_time;
        outfile << "bruteforce matmul," << size << "," << avgtime << "\n";
    }

    // matmul_ordinary
    for(size_t i = low_bound; i <= up_bound; i += step){
        long long avgtime = 0;
        int size = i;
        for(int time = 0; time < repeat_time; time++){
            auto m1 = generate_random_matrix(size, size);
            auto m2 = generate_random_matrix(size, size);
            long long time_taken = measure_time(matmul_ordinary, m1, m2);
            avgtime += time_taken;
        }
        avgtime /= repeat_time;
        outfile << "ordinary matmul," << size << "," << avgtime << "\n";
    }

    // matmul_strassen
    for(size_t i = low_bound; i <= up_bound; i *= 2){
        long long avgtime = 0;
        int size = i;
        for(int time = 0; time < repeat_time; time++){
            auto m1 = generate_random_matrix(size, size);
            auto m2 = generate_random_matrix(size, size);
            long long time_taken = measure_time(matmul_strassen, m1, m2);
            avgtime += time_taken;
        }
        avgtime /= repeat_time;
        outfile << "strassen matmul," << size << "," << avgtime << "\n";
    }

    // // matmul_strassen_padding
    // for(size_t i = low_bound; i <= up_bound; i += step){
    //     long long avgtime = 0;
    //     int size = i;
    //     for(int time = 0; time < repeat_time; time++){
    //         auto m1 = generate_random_matrix(size, size);
    //         auto m2 = generate_random_matrix(size, size);
    //         long long time_taken = measure_time(matmul_strassen_padding, m1, m2);
    //         avgtime += time_taken;
    //     }
    //     avgtime /= repeat_time;
    //     outfile << "strassen_padding matmul," << size << "," << avgtime << "\n";
    // }

    // matmul_ordinary(index)
    for(size_t i = low_bound; i <= up_bound; i += step){
        long long avgtime = 0;
        int size = i;
        for(int time = 0; time < repeat_time; time++){
            auto m1 = generate_random_matrix(size, size);
            auto m2 = generate_random_matrix(size, size);
            long long time_taken = measure_time(matmul_ordinary_index, m1, m2);
            avgtime += time_taken;
        }
        avgtime /= repeat_time;
        outfile << "ordinary matmul(index)," << size << "," << avgtime << "\n";
    }

    // matmul_strassen(index)
    for(size_t i = low_bound; i <= up_bound; i *= 2){
        long long avgtime = 0;
        int size = i;
        for(int time = 0; time < repeat_time; time++){
            auto m1 = generate_random_matrix(size, size);
            auto m2 = generate_random_matrix(size, size);
            long long time_taken = measure_time(matmul_strassen_index, m1, m2);
            avgtime += time_taken;
        }
        avgtime /= repeat_time;
        outfile << "strassen matmul(index)," << size << "," << avgtime << "\n";
    }

    // // matmul_strassen_padding(index)
    // for(size_t i = low_bound; i <= up_bound; i += step){
    //     long long avgtime = 0;
    //     int size = i;
    //     for(int time = 0; time < repeat_time; time++){
    //         auto m1 = generate_random_matrix(size, size);
    //         auto m2 = generate_random_matrix(size, size);
    //         long long time_taken = measure_time(matmul_strassen_index_padding, m1, m2);
    //         avgtime += time_taken;
    //     }
    //     avgtime /= repeat_time;
    //     outfile << "strassen_padding matmul(index)," << size << "," << avgtime << "\n";
    // }
    outfile.close();

    return 0;
}
