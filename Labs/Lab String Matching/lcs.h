#pragma once
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> longset_common_subseqence(vector<string> s1, vector<string> s2){
    int l1 = s1.size();
    int l2 = s2.size();
    /*Matrix to record the length of the lcs of the sub_strings*/
    int len_matrix[l1 + 1][l2 + 1];
    for(int i = 0; i < l1 + 1; i++){
        len_matrix[i][0] = 0;
    }
    for(int j = 0; j < l2 + 1; j++){
        len_matrix[0][j] = 0;
    }
    /*Matrix to record the direction, in order to rebuild the result*/
    // 0 : from (i - 1, j - 1)
    // 1 : from (i, j - 1)
    // 2 : from (i - 1, j)
    int dir_matrix[l1 + 1][l2 + 1];

    for(int i = 1; i < l1 + 1; i++){
        for(int j = 1; j < l2 + 1; j++){
            //if the elements match
            if(s1[i - 1] == s2[j - 1]){
                len_matrix[i][j] = len_matrix[i - 1][j - 1] + 1;
                dir_matrix[i][j] = 0;
            }
            else if(len_matrix[i][j - 1] >= len_matrix[i - 1][j]){
                len_matrix[i][j] = len_matrix[i][j - 1];
                dir_matrix[i][j] = 1;
            }
            else{
                len_matrix[i][j] = len_matrix[i - 1][j];
                dir_matrix[i][j] = 2;
            }
        }
    }

    vector<string> ret;
    int max_len = len_matrix[l1][l2];
    int p1 = l1, p2 = l2;
    while(p1 != 0 && p2 != 0){
        if(dir_matrix[p1][p2] == 0){
            ret.push_back(s1[p1 - 1]);
            p1 -= 1;
            p2 -= 1;
        }
        else if(dir_matrix[p1][p2] == 1){
            p2 -= 1;            
        }
        else if(dir_matrix[p1][p2] == 2){
            p1 -= 1;
        }
    }

    reverse(ret.begin(), ret.end());
    return ret;
}
