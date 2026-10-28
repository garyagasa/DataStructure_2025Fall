#pragma once
#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<vector<int>> matadd( vector<vector<int>>& m1, 
                            vector<vector<int>>& m2, 
                            int m1_row_begin,
                            int m1_row_end,
                            int m1_col_begin,
                            int m1_col_end,
                            int m2_row_begin,
                            int m2_row_end,
                            int m2_col_begin,
                            int m2_col_end){
    // matrix shape check
    if((m1_row_end - m1_row_begin != m2_row_end - m2_row_begin) || (m1_col_end - m1_col_begin!= m2_col_end - m2_col_begin)){
        throw invalid_argument("matrixes' sizes don't match in adding");
    }
    // m1 is (m * n), m2 is (m * n)
    int m = m1_row_end - m1_row_begin;
    int n = m1_col_end - m1_col_begin;
    vector<vector<int>> ret(m, vector<int>(n));
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            ret[i][j] = m1[i + m1_row_begin][j + m1_col_begin] + m2[i + m2_row_begin][j + m2_col_begin];
        }
    }
    return ret;
}

vector<vector<int>> matsub( vector<vector<int>>& m1, 
                            vector<vector<int>>& m2, 
                            int m1_row_begin,
                            int m1_row_end,
                            int m1_col_begin,
                            int m1_col_end,
                            int m2_row_begin,
                            int m2_row_end,
                            int m2_col_begin,
                            int m2_col_end){
    // matrix shape check
    if((m1_row_end - m1_row_begin != m2_row_end - m2_row_begin) || (m1_col_end - m1_col_begin!= m2_col_end - m2_col_begin)){
        throw invalid_argument("matrixes' sizes don't match in adding");
    }
    // m1 is (m * n), m2 is (m * n)
    int m = m1_row_end - m1_row_begin;
    int n = m1_col_end - m1_col_begin;
    vector<vector<int>> ret(m, vector<int>(n));
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            ret[i][j] = m1[i + m1_row_begin][j + m1_col_begin] - m2[i + m2_row_begin][j + m2_col_begin];
        }
    }
    return ret;
}