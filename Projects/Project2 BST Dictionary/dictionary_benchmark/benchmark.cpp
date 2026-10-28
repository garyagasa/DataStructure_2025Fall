#include <chrono>
#include <random>
#include "../io.h"
#include "../bst/red_black.h"
#include "../bst/avl.h"
using namespace std;

string random_string(int len=6) {
    string s;
    static const char chars[] = "abcdefghijklmnopqrstuvwxyz";
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    for (int i = 0; i < len; ++i) {
        s += chars[gen() % 26];
    }
    return s;
}

int main(){
    vector<pair<string, string>> df1 = read_txt_double("../data/init.txt");
    vector<string> df2 = read_txt_single("../data/delete.txt");
    vector<pair<string, string>> df3 = read_txt_double("../data/insert.txt");
    
    // Initialize the red_black dictionary and avl dictionary
    red_black_tree<string> rb1;
    avl<string> avl1;

    // Output to the csv file "result.csv"
    std::ofstream outfile("./init_benchmark.csv");
    outfile << "bst_type,node_number,time/100 insertion\n";

    // RED-BLACK Initialize Benchmark
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    long long duration = 0;
    for(int i = 0; i < df1.size(); i++){
        auto [english, chinese] = df1[i];
        if(i % 100 == 0 || i == (df1.size() - 1)){
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            outfile << "red_black," << i << "," << duration << "\n";
            start = std::chrono::high_resolution_clock::now();        
        }
        rb1.tree_insert(english, chinese);
    }

    // AVL Initialize Benchmark
    start = std::chrono::high_resolution_clock::now();
    end = std::chrono::high_resolution_clock::now();
    duration = 0;
    for(int i = 0; i < df1.size(); i++){
        auto [english, chinese] = df1[i];
        if(i % 100 == 0 || i == (df1.size() - 1)){
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            outfile << "avl," << i << "," << duration << "\n";
            start = std::chrono::high_resolution_clock::now();        
        }
        avl1.tree_insert(english, chinese);
    }
    outfile.close();

    // RED-BLACK Delete-Insert Benchmark
    long long total_delete_time = 0;
    long long total_insert_time = 0;
    int repeat_time1 = 200;
        
    start = std::chrono::high_resolution_clock::now();
    end = std::chrono::high_resolution_clock::now();
    duration = 0;
    for(int i = 0; i < repeat_time1; i++){
        // Delete
        start = std::chrono::high_resolution_clock::now();
        for(auto english : df2){
            auto p = rb1.tree_search(english);
            if (p != nullptr) {
                rb1.tree_delete(p);
            }
        }
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        total_delete_time += duration;
        // Insert
        start = std::chrono::high_resolution_clock::now();
        for(auto [english, chinese] : df3){
            rb1.tree_insert(english, chinese);
        }
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        total_insert_time += duration;
    }

    std::cout << "red-black average delete time(ms): " << total_delete_time / repeat_time1 << std::endl;
    std::cout << "red-black average insert time(ms): " << total_insert_time / repeat_time1 << std::endl;

    // AVL Delete-Insert Benchmark
    total_delete_time = 0;
    total_insert_time = 0;
    int repeat_time2 = 200;
        
    start = std::chrono::high_resolution_clock::now();
    end = std::chrono::high_resolution_clock::now();
    duration = 0;
    for(int i = 0; i < repeat_time2; i++){
        // Delete
        start = std::chrono::high_resolution_clock::now();
        for(auto english : df2){
            auto p = avl1.tree_search(english);
            if (p != nullptr) {
                avl1.tree_delete(p);
            }
        }
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        total_delete_time += duration;
        // Insert
        start = std::chrono::high_resolution_clock::now();
        for(auto [english, chinese] : df3){
            avl1.tree_insert(english, chinese);
        }
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        total_insert_time += duration;
    }

    std::cout << "avl average delete time(ms): " << total_delete_time / repeat_time2 << std::endl;
    std::cout << "avl average insert time(ms): " << total_insert_time / repeat_time2 << std::endl;

    // RED-BLACK Search
    long long total_search_time = 0; 
    int repeat_time3 = 200;

    start = std::chrono::high_resolution_clock::now();
    end = std::chrono::high_resolution_clock::now();
    duration = 0;
    for(int i = 0; i < repeat_time3; i++){
        start = std::chrono::high_resolution_clock::now();
        string english = random_string();
        auto p = rb1.tree_search(english);
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        total_search_time += duration;
    }
    std::cout << "red-black average search time(ns): " << total_search_time / repeat_time3 << std::endl;

    // AVL Search
    total_search_time = 0; 
    int repeat_time4 = 200;

    start = std::chrono::high_resolution_clock::now();
    end = std::chrono::high_resolution_clock::now();
    duration = 0;
    for(int i = 0; i < repeat_time4; i++){
        start = std::chrono::high_resolution_clock::now();
        string english = random_string();
        auto p = avl1.tree_search(english);
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        total_search_time += duration;
    }
    std::cout << "avl average search time(ns): " << total_search_time / repeat_time3 << std::endl;

    // RED-BLACK Range Search
    total_search_time = 0; 
    int repeat_time5 = 200;

    start = std::chrono::high_resolution_clock::now();
    end = std::chrono::high_resolution_clock::now();
    duration = 0;
    for(int i = 0; i < repeat_time5; i++){
        start = std::chrono::high_resolution_clock::now();
        string english1 = random_string();
        string english2 = random_string();
        auto p = rb1.range_search(english1, english2);
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        total_search_time += duration;
    }
    std::cout << "red-black average range search time(ns): " << total_search_time / repeat_time5 << std::endl;

    // AVL Range Search
    total_search_time = 0; 
    int repeat_time6 = 200;

    start = std::chrono::high_resolution_clock::now();
    end = std::chrono::high_resolution_clock::now();
    duration = 0;
    for(int i = 0; i < repeat_time5; i++){
        start = std::chrono::high_resolution_clock::now();
        string english1 = random_string();
        string english2 = random_string();
        auto p = avl1.range_search(english1, english2);
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        total_search_time += duration;
    }
    std::cout << "avl average range search time(ns): " << total_search_time / repeat_time6 << std::endl;

    return 0;
}