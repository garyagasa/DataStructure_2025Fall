#pragma once
#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include "matadd.h"
#include "next_power_of_2.h"
#define ordinary_switch 2
#define strassen_switch 2

using namespace std;

void matmul_ordinary_index_helper(  vector<vector<int>>& m1, 
                                    vector<vector<int>>& m2,
                                    vector<vector<int>>& result,
                                    int m1_row_begin, int m1_row_end,
                                    int m1_col_begin, int m1_col_end,
                                    int m2_row_begin, int m2_row_end,
                                    int m2_col_begin, int m2_col_end);

void matmul_strassen_index_helper(vector<vector<int>>& m1, 
                                vector<vector<int>>& m2,
                                vector<vector<int>>& result,
                                int m1_row_begin, int m1_row_end,
                                int m1_col_begin, int m1_col_end,
                                int m2_row_begin, int m2_row_end,
                                int m2_col_begin, int m2_col_end,
                                int ret_row_begin, int ret_col_begin);

vector<vector<int>> matmul_ordinary_index(vector<vector<int>>& m1, vector<vector<int>>& m2) {
    if (m1[0].size() != m2.size()) {
        throw invalid_argument("matrix sizes don't match");
    }
    
    int m = m1.size();
    int n = m1[0].size();
    int p = m2[0].size();
    
    vector<vector<int>> result(m, vector<int>(p, 0));
    matmul_ordinary_index_helper(m1, m2, result, 0, m, 0, n, 0, n, 0, p);
    return result;
}

void matmul_ordinary_index_helper(  vector<vector<int>>& m1, 
                                    vector<vector<int>>& m2,
                                    vector<vector<int>>& result,
                                    int m1_row_begin, int m1_row_end,
                                    int m1_col_begin, int m1_col_end,
                                    int m2_row_begin, int m2_row_end,
                                    int m2_col_begin, int m2_col_end) {
    
    int m = m1_row_end - m1_row_begin;
    int n = m1_col_end - m1_col_begin;
    int p = m2_col_end - m2_col_begin;
    
    // recursive bar, directly compute the small matrixes using bruteforce algorithm
    if (m <= ordinary_switch || n <= ordinary_switch || p <= ordinary_switch) {
        for (int i = 0; i < m; i++) {
            for (int k = 0; k < n; k++) {
                for (int j = 0; j < p; j++) {
                    result[m1_row_begin + i][m2_col_begin + j] += 
                        m1[m1_row_begin + i][m1_col_begin + k] * 
                        m2[m2_row_begin + k][m2_col_begin + j];
                }
            }
        }
        return;
    }
    
    int m1_row_mid = (m1_row_begin + m1_row_end) / 2;
    int m1_col_mid = (m1_col_begin + m1_col_end) / 2;
    int m2_row_mid = (m2_row_begin + m2_row_end) / 2;
    int m2_col_mid = (m2_col_begin + m2_col_end) / 2;
    
    // C11 = A11 * B11 + A12 * B21
    matmul_ordinary_index_helper(m1, m2, result, 
                                m1_row_begin, m1_row_mid, m1_col_begin, m1_col_mid,
                                m2_row_begin, m2_row_mid, m2_col_begin, m2_col_mid);
    matmul_ordinary_index_helper(m1, m2, result,
                                m1_row_begin, m1_row_mid, m1_col_mid, m1_col_end,
                                m2_row_mid, m2_row_end, m2_col_begin, m2_col_mid);
    
    // C12 = A11 * B12 + A12 * B22
    matmul_ordinary_index_helper(m1, m2, result,
                                m1_row_begin, m1_row_mid, m1_col_begin, m1_col_mid,
                                m2_row_begin, m2_row_mid, m2_col_mid, m2_col_end);
    matmul_ordinary_index_helper(m1, m2, result,
                                m1_row_begin, m1_row_mid, m1_col_mid, m1_col_end,
                                m2_row_mid, m2_row_end, m2_col_mid, m2_col_end);
    
    // C21 = A21 * B11 + A22 * B21
    matmul_ordinary_index_helper(m1, m2, result,
                                m1_row_mid, m1_row_end, m1_col_begin, m1_col_mid,
                                m2_row_begin, m2_row_mid, m2_col_begin, m2_col_mid);
    matmul_ordinary_index_helper(m1, m2, result,
                                m1_row_mid, m1_row_end, m1_col_mid, m1_col_end,
                                m2_row_mid, m2_row_end, m2_col_begin, m2_col_mid);
    
    // C22 = A21 * B12 + A22 * B22
    matmul_ordinary_index_helper(m1, m2, result,
                                m1_row_mid, m1_row_end, m1_col_begin, m1_col_mid,
                                m2_row_begin, m2_row_mid, m2_col_mid, m2_col_end);
    matmul_ordinary_index_helper(m1, m2, result,
                                m1_row_mid, m1_row_end, m1_col_mid, m1_col_end,
                                m2_row_mid, m2_row_end, m2_col_mid, m2_col_end);
}

vector<vector<int>> matmul_strassen_index(vector<vector<int>>& m1, vector<vector<int>>& m2) {
    if (m1[0].size() != m2.size()) {
        throw invalid_argument("matrix sizes don't match");
    }
    int m = m1.size();
    int n = m1[0].size();
    int p = m2[0].size();
    if((m != n) || (n != p)){
        throw invalid_argument("doesn't support the matrixes not square");
    }
    if(next_power_of_2(n) != n){
        throw invalid_argument("doesn't support the matrixes whose nums of row is not 2^n");
    }
    vector<vector<int>> result(n, vector<int>(n, 0));
    matmul_strassen_index_helper(m1, m2, result, 0, n, 0, n, 0, n, 0, n, 0, 0);
    return result;
}

vector<vector<int>> matmul_strassen_index_padding(vector<vector<int>>& m1, vector<vector<int>>& m2){
    // matrix shape check
    if(m1[0].size() != m2.size()){
        throw invalid_argument("matrixes' sizes don't match");
    }
    // m1 is (m * n), m2 is (n * p)
    int m = m1.size();
    int n = m1[0].size();
    int p = m2[0].size();

    int max_dim = max({m, n, p});
    int padded_dim = next_power_of_2(max_dim);

    vector<vector<int>> m1_padded(padded_dim, vector<int>(padded_dim, 0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            m1_padded[i][j] = m1[i][j];
        }
    }

    vector<vector<int>> m2_padded(padded_dim, vector<int>(padded_dim, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            m2_padded[i][j] = m2[i][j];
        }
    }

    vector<vector<int>> ret_padded(padded_dim, vector<int>(padded_dim, 0)); 
    matmul_strassen_index_helper(m1_padded, m2_padded, ret_padded, 
                                0, padded_dim,
                                0, padded_dim,
                                0, padded_dim, 
                                0, padded_dim,
                                0, 0);
    
    vector<vector<int>> ret(m, vector<int>(p));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            ret[i][j] = ret_padded[i][j];
        }
    }

    return ret;
}

void matmul_strassen_index_helper(vector<vector<int>>& m1, 
                                vector<vector<int>>& m2,
                                vector<vector<int>>& result,
                                int m1_row_begin, int m1_row_end,
                                int m1_col_begin, int m1_col_end,
                                int m2_row_begin, int m2_row_end,
                                int m2_col_begin, int m2_col_end,
                                int ret_row_begin, int ret_col_begin) {
    
    int n = m1_row_end - m1_row_begin;
    
    // recursive bar, directly compute the small matrixes using bruteforce algorithm
    if (n <= strassen_switch) {
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                for (int j = 0; j < n; j++) {
                    result[ret_row_begin + i][ret_col_begin + j] += 
                        m1[m1_row_begin + i][m1_col_begin + k] * 
                        m2[m2_row_begin + k][m2_col_begin + j];
                }
            }
        }
        return;
    }
    
    int mid = n / 2;
    int m1_row_middle = (m1_row_begin + m1_row_end) / 2;
    int m1_col_middle = (m1_col_begin + m1_col_end) / 2;
    int m2_row_middle = (m2_row_begin + m2_row_end) / 2;
    int m2_col_middle = (m2_col_begin + m2_col_end) / 2;

    // S matrixes
    vector<vector<int>> s1 = matsub(m2, m2, m2_row_begin, m2_row_middle, m2_col_middle, m2_col_end,
                                        m2_row_middle, m2_row_end, m2_col_middle, m2_col_end);
    vector<vector<int>> s2 = matadd(m1, m1, m1_row_begin, m1_row_middle, m1_col_begin, m1_col_middle,
                                        m1_row_begin, m1_row_middle, m1_col_middle, m1_col_end);

    vector<vector<int>> s3 = matadd(m1, m1, m1_row_middle, m1_row_end, m1_col_begin, m1_col_middle,
                                        m1_row_middle, m1_row_end, m1_col_middle, m1_col_end);

    vector<vector<int>> s4 = matsub(m2, m2, m2_row_middle, m2_row_end, m2_col_begin, m2_col_middle,
                                        m2_row_begin, m2_row_middle, m2_col_begin, m2_col_middle);
        
    vector<vector<int>> s5 = matadd(m1, m1, m1_row_begin, m1_row_middle, m1_col_begin, m1_col_middle,
                                        m1_row_middle, m1_row_end, m1_col_middle, m1_col_end);
        
    vector<vector<int>> s6 = matadd(m2, m2, m2_row_begin, m2_row_middle, m2_col_begin, m2_col_middle,
                                        m2_row_middle, m2_row_end, m2_col_middle, m2_col_end);
        
    vector<vector<int>> s7 = matsub(m1, m1, m1_row_begin, m1_row_middle, m1_col_middle, m1_col_end,
                                        m1_row_middle, m1_row_end, m1_col_middle, m1_col_end);
        
    vector<vector<int>> s8 = matadd(m2, m2, m2_row_middle, m2_row_end, m2_col_begin, m2_col_middle,
                                        m2_row_middle, m2_row_end, m2_col_middle, m2_col_end);
        
    vector<vector<int>> s9 = matsub(m1, m1, m1_row_begin, m1_row_middle, m1_col_begin, m1_col_middle,
                                        m1_row_middle, m1_row_end, m1_col_begin, m1_col_middle);
        
    vector<vector<int>> s10 = matadd(m2, m2, m2_row_begin, m2_row_middle, m2_col_begin, m2_col_middle,
                                        m2_row_begin, m2_row_middle, m2_col_middle, m2_col_end);

    // pre allocate temporary memory for p matrixes(avoid allocating again)
    vector<vector<int>> p1(mid, vector<int>(mid));
    vector<vector<int>> p2(mid, vector<int>(mid));
    vector<vector<int>> p3(mid, vector<int>(mid));
    vector<vector<int>> p4(mid, vector<int>(mid));
    vector<vector<int>> p5(mid, vector<int>(mid));
    vector<vector<int>> p6(mid, vector<int>(mid));
    vector<vector<int>> p7(mid, vector<int>(mid));
    
    // P matrixes
    matmul_strassen_index_helper(m1, s1, p1, 
                                m1_row_begin, m1_row_middle,
                                m1_col_begin, m1_col_middle,
                                0, mid,
                                0, mid,
                                0, 0);
    
    matmul_strassen_index_helper(s2, m2, p2,
                                0, mid, 
                                0, mid,
                                m2_row_middle, m2_row_end,
                                m2_col_middle, m2_col_end,
                                0, 0);
    
    matmul_strassen_index_helper(s3, m2, p3,
                                0, mid, 
                                0, mid,
                                m2_row_begin, m2_row_middle, 
                                m2_col_begin, m2_col_middle,
                                0, 0);
        
    matmul_strassen_index_helper(m1, s4, p4,
                                m1_row_middle, m1_row_end, 
                                m1_col_middle, m1_col_end,
                                0, mid, 
                                0, mid,
                                0, 0);
        
    matmul_strassen_index_helper(s5, s6, p5, 
                                0, mid, 
                                0, mid,
                                0, mid, 
                                0, mid,
                                0, 0);

    matmul_strassen_index_helper(s7, s8, p6, 
                                0, mid, 
                                0, mid,
                                0, mid, 
                                0, mid,
                                0, 0);

    matmul_strassen_index_helper(s9, s10, p7, 
                                0, mid, 
                                0, mid,
                                0, mid, 
                                0, mid,
                                0, 0);

    // Calculating the final result
    // C_11
    for(int i = 0; i < m1_row_middle - m1_row_begin; i++){
        for(int j = 0; j < m2_col_middle - m2_col_begin; j++){ 
            result[i + ret_row_begin][j + ret_col_begin] = p5[i][j] + p4[i][j] -p2[i][j] + p6[i][j];
        }
    }
    // C_12
    for(int i = 0; i < m1_row_middle - m1_row_begin; i++){
        for(int j = m2_col_middle - m2_col_begin; j < m2_col_end - m2_col_begin; j++){ 
            result[i + ret_row_begin][j + ret_col_begin] = p1[i][j - (m2_col_middle - m2_col_begin)] + p2[i][j - (m2_col_middle - m2_col_begin)];
        }
    }
    // C_21
    for(int i = m1_row_middle - m1_row_begin; i < m1_row_end - m1_row_begin; i++){
        for(int j = 0; j < m2_col_middle - m2_col_begin; j++){ 
            result[i + ret_row_begin][j + ret_col_begin] = p3[i - (m1_row_middle - m1_row_begin)][j] + p4[i - (m1_row_middle - m1_row_begin)][j];
        }
    }
    // C_22
    for(int i = m1_row_middle - m1_row_begin; i < m1_row_end - m1_row_begin; i++){
        for(int j = m2_col_middle - m2_col_begin; j < m2_col_end - m2_col_begin; j++){
            result[i + ret_row_begin][j + ret_col_begin] = p5[i - (m1_row_middle - m1_row_begin)][j - (m2_col_middle - m2_col_begin)] + 
                            p1[i - (m1_row_middle - m1_row_begin)][j - (m2_col_middle - m2_col_begin)] -
                            p3[i - (m1_row_middle - m1_row_begin)][j - (m2_col_middle - m2_col_begin)] -
                            p7[i - (m1_row_middle - m1_row_begin)][j - (m2_col_middle - m2_col_begin)];
        }
    }
    return;
}