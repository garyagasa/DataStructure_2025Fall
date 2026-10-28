#pragma once
#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
using namespace std;

vector<string> string2vec(string expression) {
    vector<string> ret;
    string currentNumber = "";
    
    for (size_t i = 0; i < expression.length(); ++i) {
        char c = expression[i];
        // skip ' '
        if (c == ' ') {
            continue;
        }
        
        // 处理数字
        if (isdigit(c)) {
            currentNumber += c;
        }
        // 处理负数（当前字符是'-'，前面没有数字或运算符，且后面是数字）
        else if (c == '-' && (i == 0 || expression[i-1] == '(' || expression[i-1] == '[') 
                 && i+1 < expression.length() && isdigit(expression[i+1])) {
            currentNumber += c;
        }
        // 处理运算符和括号
        else {
            // 如果已经有数字在处理中，先加入结果
            if (!currentNumber.empty()) {
                ret.push_back(currentNumber);
                currentNumber = "";
            }
            // 将运算符或括号加入结果
            ret.push_back(string(1, c));
        }
    }
    
    // 处理最后可能剩余的数字
    if (!currentNumber.empty()) {
        ret.push_back(currentNumber);
    }
    
    return ret;
}