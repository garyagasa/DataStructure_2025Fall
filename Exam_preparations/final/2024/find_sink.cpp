#include <cstdio>
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

int FindSink(vector<vector<int>> M){
    int n = M.size();

    int check_p = 0;
    while(check_p < n){
        bool is_possble = true;
        bool finish_check = false;
        for(int i = check_p + 1; i < n;){
            // Check the row: find 0 or find all of them are 1
            // Check the column: find 1 or find all of them are 0
            if(M[check_p][i] == 0 && M[i][check_p] == 1){
                i++;
            }
            // This check_point is not possible, check the next possible one
            else if(M[check_p][i] == 1 && M[i][check_p] == 0){
                check_p = i;
                is_possble = false;
                break;
            }
            else{
                if(i == n - 1)
                    finish_check = true;
                i++;
                is_possble = false;
            }
        }
        
        // find the possble solution(only one candidate is enough)
        if(is_possble){
            break;
        }
        else if(finish_check){
            return -1;
        }
    }

    // Check if the candidate is the right answer
    if(check_p == n){
        return -1;
    }
    bool is_right = true;
    for(int i = 0; i < check_p; i++){
        // Find exception
        if(M[check_p][i] == 1 || M[i][check_p] == 0){
            is_right = false;
        }
    }

    return is_right ? check_p : -1;
}

int main(){
    vector<vector<int>> test1({{0, 1, 0}, {0, 0, 1}, {1, 0, 0}});
    int ret1 = FindSink(test1);
    assert(ret1 == -1);

    // 测试2：有sink点（2号点为sink）
    vector<vector<int>> test2({{0, 1, 1}, {0, 0, 1}, {0, 0, 0}});
    int ret2 = FindSink(test2);
    assert(ret2 == 2);

    // 测试3：只有一个点
    vector<vector<int>> test3({{0}});
    int ret3 = FindSink(test3);
    assert(ret3 == 0);

    // 测试4：无sink点（全互相指向）
    vector<vector<int>> test4({{0,1,1},{1,0,1},{1,1,0}});
    int ret4 = FindSink(test4);
    assert(ret4 == -1);

    // 测试5：有sink点（0号点为sink）
    vector<vector<int>> test5({{0,0,0},{1,0,1},{1,0,0}});
    int ret5 = FindSink(test5);
    assert(ret5 == 0);

    // 测试6：有sink点（只有一条边）
    vector<vector<int>> test6({{0,1},{0,0}});
    int ret6 = FindSink(test6);
    assert(ret6 == 1);

        // 大样例1：10个点，9号为sink
        vector<vector<int>> big1(10, vector<int>(10, 0));
        for(int i = 0; i < 10; ++i) {
            for(int j = 0; j < 10; ++j) {
                if(i != 9 && j == 9) big1[i][j] = 1; // 其他点都指向9
            }
        }
        int ret_big1 = FindSink(big1);
        assert(ret_big1 == 9);

        // 大样例2：20个点，无sink
        vector<vector<int>> big2(20, vector<int>(20, 0));
        for(int i = 0; i < 20; ++i) {
            for(int j = 0; j < 20; ++j) {
                if(i != j) big2[i][j] = 1; // 全互相指向
            }
        }
        int ret_big2 = FindSink(big2);
        assert(ret_big2 == -1);

        // 大样例3：15个点，0号为sink
        vector<vector<int>> big3(15, vector<int>(15, 0));
        for(int i = 1; i < 15; ++i) {
            big3[i][0] = 1; // 其他点都指向0
        }
        int ret_big3 = FindSink(big3);
        assert(ret_big3 == 0);

        // 大样例4：12个点，随机无sink
        vector<vector<int>> big4(12, vector<int>(12, 0));
        for(int i = 0; i < 12; ++i) {
            for(int j = 0; j < 12; ++j) {
                if(i != j && (i+j)%3==0) big4[i][j] = 1;
            }
        }
        int ret_big4 = FindSink(big4);
        assert(ret_big4 == -1);
    

        
    cout << "pass all tests :)" << endl;
    return 0;
}