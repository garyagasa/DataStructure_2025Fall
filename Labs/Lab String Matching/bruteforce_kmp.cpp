#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int bruteforce_match(string P, string T){
    size_t n = P.size();
    size_t m = T.size();
    int i = 0, j = 0;   
    // i -> char to compare in T
    // j -> char to compare in P
    
    while(j < m && i < n){
        /* When we exit the loop:
            if "j == m", it means that we have successfully 
                match the target string
            else if "i == n", it means that we fail to match
        */

        // If this char is match, then we compare the next one
        if(T[i] == P[j]){
            i++;
            j++;
        }
        else{
            i -= (j - 1);
            j = 0;
        }
    }
    return i - j;
    // i - j > n - m : success
    // i - j < n - m : fail 
}

vector<int> buildNext(string P){
    size_t m =  P.size();
    int j = 0;
    vector<int> ret(m);
    
    ret[0] = -1;
    int t = -1;

    while(j < m - 1){
        // match
        if(0 > t || P[t] == P[j]){
            j += 1;
            t += 1;
            ret[j] = ret[t];
        }
        // not match
        else{
            t = ret[t];
        }
    }
    return ret;
}

int kmp_match(string P, string T){
    vector<int> next_table = buildNext(P);
    int n = P.size();
    int m = P.size();
    int i = 0, j = 0;   
    // i -> char to compare in T
    // j -> char to compare in P

    while(j < m && i < n){
        if(j < 0 || T[i] == P[j]){
            i++;
            j++;
        }
        else{
            j = next_table[j];
        }
    }
    return i - j;
}

/* **************************************************************** */
// 计算next数组(课本P154)
vector<int> computeNext(const string& P) {
    int m = P.length();
    vector<int> next(m, -1);  // 初始化 next 数组，长度为 m
    int k = -1;  // 前缀的末尾位置
    int j = 0;   // 当前匹配的字符位置

    while (j < m - 1) {
        if (k == -1 || P[j] == P[k]) {  // 找到相同的前后缀
            j++;
            k++;
            next[j] = k;   // 将 k(前缀的长度)赋给 next[j]
        } else {
            k = next[k];  // 回退，寻找更短的前缀
        }
    }
    return next;
}

// KMP匹配算法(课本P152)
int Find_KMP(const string& text, const string& pattern) {
    int posP = 0, posT = 0;
    int lengthP = pattern.length();
    int lengthT = text.length();

    // 计算模式串的 next 数组
    vector<int> next = computeNext(pattern);

    // KMP 字符串匹配算法
    while (posP < lengthP && posT < lengthT) {
        if (posP == -1 || pattern[posP] == text[posT]) {
            posP++;
            posT++;
        } else {
            posP = next[posP];  // 使用 next 数组回退
        }
    }

    // 如果 posP 遍历完模式串，则匹配成功，返回匹配的起始位置
    if (posP < lengthP) {
        return -1;  // 匹配失败
    } else {
        return posT - lengthP;  // 返回匹配的起始位置
    }
}

