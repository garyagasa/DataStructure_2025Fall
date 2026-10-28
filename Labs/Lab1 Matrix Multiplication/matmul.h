#pragma once
#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include "matadd.h"
#include "next_power_of_2.h"

using namespace std;

vector<vector<int>> matmul_ordinary_helper(vector<vector<int>>&, vector<vector<int>>&, int, int, int, int, int, int, int, int);
vector<vector<int>> matmul_strassen_helper(vector<vector<int>>&, vector<vector<int>>&, int, int, int, int, int, int, int, int);

// TO-DO: Implement the ordinary method for the matrix multiplication 
vector<vector<int>> matmul_ordinary(vector<vector<int>>& m1, vector<vector<int>>& m2){
    // matrix shape check
    if(m1[0].size() != m2.size()){
        throw invalid_argument("matrixes' sizes don't match in ordinary");
    }
    // m1 is (m * n), m2 is (n * p)
    int m = m1.size();
    int n = m1[0].size();
    int p = m2[0].size();
    vector<vector<int>> ret = matmul_ordinary_helper(m1, m2, 0, m, 0, n, 0, n, 0, p);
    return ret;
}

vector<vector<int>> matmul_ordinary_helper( vector<vector<int>>& m1, 
                                            vector<vector<int>>& m2, 
                                            int m1_row_begin,
                                            int m1_row_end,
                                            int m1_col_begin,
                                            int m1_col_end,
                                            int m2_row_begin,
                                            int m2_row_end,
                                            int m2_col_begin,
                                            int m2_col_end){
    if(m1_col_end - m1_col_begin != m2_row_end - m2_row_begin){
        throw invalid_argument("matrixes' sizes don't match in ordinary helper");
    }
    // the end is exclusive
    int m = m1_row_end - m1_row_begin;
    int n = m1_col_end - m1_col_begin;
    int p = m2_col_end - m2_col_begin;

    if(m == 0 || n == 0 || p == 0){
        // return an empty matrix, since we won't use it in the future
        vector<vector<int>> ret;
        return ret;
    }
    else if(m == 1 && n == 1 && p == 1){
        int result = m1[m1_row_begin][m1_col_begin] * m2[m2_row_begin][m2_col_begin];
        return vector<vector<int>>(1, vector<int>({result}));
    }
    else{
        vector<vector<int>> ret(m, vector<int>(p));

        int m1_row_middle = (m1_row_begin + m1_row_end) / 2;
        int m1_col_middle = (m1_col_begin + m1_col_end) / 2;
        int m2_row_middle = (m2_row_begin + m2_row_end) / 2;
        int m2_col_middle = (m2_col_begin + m2_col_end) / 2;
        
        // -------------------------------------------------------------------------------
        // A_11 * B_11
        vector<vector<int>> item1 = matmul_ordinary_helper( m1, m2,
                                                            m1_row_begin, m1_row_middle,
                                                            m1_col_begin, m1_col_middle,
                                                            m2_row_begin, m2_row_middle,
                                                            m2_col_begin, m2_col_middle);
        
        // A_12 * B_21
        vector<vector<int>> item2 = matmul_ordinary_helper( m1, m2,
                                                            m1_row_begin, m1_row_middle,
                                                            m1_col_middle, m1_col_end,
                                                            m2_row_middle, m2_row_end,
                                                            m2_col_begin, m2_col_middle);
        
        // C_11
        bool signal1 = (item1.size() == 0);
        bool signal2 = (item2.size() == 0);
        for(int i = 0; i < m1_row_middle - m1_row_begin; i++){
            for(int j = 0; j < m2_col_middle - m2_col_begin; j++){
                int val1 = signal1 ? 0 : item1[i][j];
                int val2 = signal2 ? 0 : item2[i][j]; 
                ret[i][j] = val1 + val2;
            }
        }
        // -----------------------------------------------------------------------------
        // A_11 * B_12
        vector<vector<int>> item3 = matmul_ordinary_helper( m1, m2,
                                                            m1_row_begin, m1_row_middle,
                                                            m1_col_begin, m1_col_middle,
                                                            m2_row_begin, m2_row_middle,
                                                            m2_col_middle, m2_col_end);
        
        // A_12 * B_22
        vector<vector<int>> item4 = matmul_ordinary_helper( m1, m2,
                                                            m1_row_begin, m1_row_middle,
                                                            m1_col_middle, m1_col_end,
                                                            m2_row_middle, m2_row_end,
                                                            m2_col_middle, m2_col_end);
        
        // C_12
        bool signal3 = (item3.size() == 0);
        bool signal4 = (item4.size() == 0);
        for(int i = 0; i < m1_row_middle - m1_row_begin; i++){
            for(int j = m2_col_middle - m2_col_begin; j < m2_col_end - m2_col_begin; j++){
                int val1 = signal3 ? 0 : item3[i][j - (m2_col_middle - m2_col_begin)];
                int val2 = signal4 ? 0 : item4[i][j - (m2_col_middle - m2_col_begin)];
                ret[i][j] = val1 + val2;
            }
        }
        //-----------------------------------------------------------------------------
        // A_21 * B_11
        vector<vector<int>> item5 = matmul_ordinary_helper( m1, m2,
                                                            m1_row_middle, m1_row_end,
                                                            m1_col_begin, m1_col_middle,
                                                            m2_row_begin, m2_row_middle,
                                                            m2_col_begin, m2_col_middle);
        
        // A_22 * B_21
        vector<vector<int>> item6 = matmul_ordinary_helper( m1, m2,
                                                            m1_row_middle, m1_row_end,
                                                            m1_col_middle, m1_col_end,
                                                            m2_row_middle, m2_row_end,
                                                            m2_col_begin, m2_col_middle);
        
        // C_21
        bool signal5 = (item5.size() == 0);
        bool signal6 = (item6.size() == 0);
        for(int i = m1_row_middle - m1_row_begin; i < m1_row_end - m1_row_begin; i++){
            for(int j = 0; j < m2_col_middle - m2_col_begin; j++){
                int val1 = signal5 ? 0 : item5[i - (m1_row_middle - m1_row_begin)][j];
                int val2 = signal6 ? 0 : item6[i - (m1_row_middle - m1_row_begin)][j];
                ret[i][j] = val1 + val2;
            }
        }
        //-----------------------------------------------------------------------------
        // A_21 * B_12
        vector<vector<int>> item7 = matmul_ordinary_helper( m1, m2,
                                                            m1_row_middle, m1_row_end,
                                                            m1_col_begin, m1_col_middle,
                                                            m2_row_begin, m2_row_middle,
                                                            m2_col_middle, m2_col_end);
        
        // A_22 * B_22
        vector<vector<int>> item8 = matmul_ordinary_helper( m1, m2,
                                                            m1_row_middle, m1_row_end,
                                                            m1_col_middle, m1_col_end,
                                                            m2_row_middle, m2_row_end,
                                                            m2_col_middle, m2_col_end);
        
        // C_22
        bool signal7 = (item7.size() == 0);
        bool signal8 = (item8.size() == 0);
        for(int i = m1_row_middle - m1_row_begin; i < m1_row_end - m1_row_begin; i++){
            for(int j = m2_col_middle - m2_col_begin; j < m2_col_end - m2_col_begin; j++){
                int val1 = signal7 ? 0 : item7[i - (m1_row_middle - m1_row_begin)][j - (m2_col_middle - m2_col_begin)] ;
                int val2 = signal8 ? 0 : item8[i - (m1_row_middle - m1_row_begin)][j - (m2_col_middle - m2_col_begin)];
                ret[i][j] = val1 + val2;
            }
        }

        //-----------------------------------------------------------------------------
        return ret;
    }
}

// TO-DO: Implement the Strassen method for the matrix multiplication 
vector<vector<int>> matmul_strassen(vector<vector<int>>& m1, vector<vector<int>>& m2){
    // matrix shape check
        // matrix shape check
    if(m1[0].size() != m2.size()){
        throw invalid_argument("matrixes' sizes don't match in strassen");
    }
    // m1 is (m * n), m2 is (n * p)
    int m = m1.size();
    int n = m1[0].size();
    int p = m2[0].size();
    if((m != n) || (n != p)){
        throw invalid_argument("doesn't support the matrixes not square");
    }
    if(next_power_of_2(n) != n){
        throw invalid_argument("doesn't support the matrixes whose nums of row is not 2^n");
    }
    vector<vector<int>> ret = matmul_strassen_helper(m1, m2, 0, m, 0, n, 0, n, 0, p);
    return ret;
}

/** We can padding the matrix whose size is not 2^n to a matrix whose size is 2^n, 
 * and then use trimming, so that we can perform the strassen algorithm to any matrix
 */ 
// TO-DO: Implement the Strassen method for the matrix multiplication with padding 
vector<vector<int>> matmul_strassen_padding(vector<vector<int>>& m1, vector<vector<int>>& m2){
    // matrix shape check
    if(m1[0].size() != m2.size()){
        throw invalid_argument("matrixes' sizes don't match in strassen");
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

    vector<vector<int>> ret_padded = matmul_strassen_helper(m1_padded, m2_padded, 
                                                            0, padded_dim, 0, padded_dim,
                                                            0, padded_dim, 0, padded_dim);
    
    vector<vector<int>> ret(m, vector<int>(p));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            ret[i][j] = ret_padded[i][j];
        }
    }

    return ret;
}

// only apply to square matrixes
vector<vector<int>> matmul_strassen_helper( vector<vector<int>>& m1, 
                                            vector<vector<int>>& m2, 
                                            int m1_row_begin,
                                            int m1_row_end,
                                            int m1_col_begin,
                                            int m1_col_end,
                                            int m2_row_begin,
                                            int m2_row_end,
                                            int m2_col_begin,
                                            int m2_col_end){
    if(m1_col_end - m1_col_begin != m2_row_end - m2_row_begin){
        throw invalid_argument("matrixes' sizes don't match in strassen helper");
    }
    // the end is exclusive
    int m = m1_row_end - m1_row_begin;
    int n = m1_col_end - m1_col_begin;
    int p = m2_col_end - m2_col_begin;

    if(m == 0 || n == 0 || p == 0){
        // return an empty matrix, since we won't use it in the future
        vector<vector<int>> ret;
        return ret;
    }
    else if(m == 1 && n == 1 && p == 1){
        int result = m1[m1_row_begin][m1_col_begin] * m2[m2_row_begin][m2_col_begin];
        return vector<vector<int>>(1, vector<int>({result}));
    }
    else{
        vector<vector<int>> ret(m, vector<int>(p));

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
        
        // P matrixes
        vector<vector<int>> p1 = matmul_strassen_helper(m1, s1, m1_row_begin, m1_row_middle, m1_col_begin, m1_col_middle,
                                                        0, s1.size(), 0, s1[0].size());

        vector<vector<int>> p2 = matmul_strassen_helper(s2, m2, 0, s2.size(), 0, s2[0].size(),
                                                        m2_row_middle, m2_row_end, m2_col_middle, m2_col_end);

        vector<vector<int>> p3 = matmul_strassen_helper(s3, m2, 0, s3.size(), 0, s3[0].size(),
                                                        m2_row_begin, m2_row_middle, m2_col_begin, m2_col_middle);
        
        vector<vector<int>> p4 = matmul_strassen_helper(m1, s4, m1_row_middle, m1_row_end, m1_col_middle, m1_col_end,
                                                        0, s4.size(), 0, s4[0].size());
        
        vector<vector<int>> p5 = matmul_strassen_helper(s5, s6, 0, s5.size(), 0, s5[0].size(),
                                                        0, s6.size(), 0, s6[0].size());

        vector<vector<int>> p6 = matmul_strassen_helper(s7, s8, 0, s7.size(), 0, s7[0].size(),
                                                        0, s8.size(), 0, s8[0].size());
        
        vector<vector<int>> p7 = matmul_strassen_helper(s9, s10, 0, s9.size(), 0, s9[0].size(),
                                                        0, s10.size(), 0, s10[0].size());

        // Calculating the final result
        // C_11
        for(int i = 0; i < m1_row_middle - m1_row_begin; i++){
            for(int j = 0; j < m2_col_middle - m2_col_begin; j++){ 
                ret[i][j] = p5[i][j] + p4[i][j] -p2[i][j] + p6[i][j];
            }
        }
        // C_12
        for(int i = 0; i < m1_row_middle - m1_row_begin; i++){
            for(int j = m2_col_middle - m2_col_begin; j < m2_col_end - m2_col_begin; j++){ 
                ret[i][j] = p1[i][j - (m2_col_middle - m2_col_begin)] + p2[i][j - (m2_col_middle - m2_col_begin)];
            }
        }
        // C_21
        for(int i = m1_row_middle - m1_row_begin; i < m1_row_end - m1_row_begin; i++){
            for(int j = 0; j < m2_col_middle - m2_col_begin; j++){ 
                ret[i][j] = p3[i - (m1_row_middle - m1_row_begin)][j] + p4[i - (m1_row_middle - m1_row_begin)][j];
            }
        }
        // C_22
        for(int i = m1_row_middle - m1_row_begin; i < m1_row_end - m1_row_begin; i++){
            for(int j = m2_col_middle - m2_col_begin; j < m2_col_end - m2_col_begin; j++){
                ret[i][j] = p5[i - (m1_row_middle - m1_row_begin)][j - (m2_col_middle - m2_col_begin)] + 
                            p1[i - (m1_row_middle - m1_row_begin)][j - (m2_col_middle - m2_col_begin)] -
                            p3[i - (m1_row_middle - m1_row_begin)][j - (m2_col_middle - m2_col_begin)] -
                            p7[i - (m1_row_middle - m1_row_begin)][j - (m2_col_middle - m2_col_begin)];
            }
        }

        return ret;
    }
}

vector<vector<int>> matmul_bruteforce(vector<vector<int>>& m1, vector<vector<int>>& m2) {
    if (m1.empty() || m2.empty() || m1[0].size() != m2.size()) {
        throw invalid_argument("matrixes' sizes don't match in bruteforce");
    }

    int m = m1.size();      
    int n = m1[0].size();   
    int p = m2[0].size();   

    vector<vector<int>> result(m, vector<int>(p, 0));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < n; ++k) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return result;
}