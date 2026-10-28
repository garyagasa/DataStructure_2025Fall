#pragma once
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<stack>
#include<vector>
#include<string>
using namespace std;

// Calculate the reverse polish calculator
int postfix_cal(vector<string>& tokens) {
    stack<int> number_stack;
    for(auto & str : tokens){
        if(str == "+" || str == "-" || str == "*" || str == "/" || str == "%"){
            // Pop two numbers to calculate
            int num2 = number_stack.top();
            number_stack.pop();
            int num1 = number_stack.top();
            number_stack.pop();

            int result  = 0;
            switch(str[0]){
                case '+':
                    result = num1 + num2;
                    break;
                case '-':
                    result = num1 - num2;
                    break;
                case '*':
                    result = num1 * num2;
                    break;
                case '/':
                    result = num1 / num2;
                    break;
                case '%':
                    result = num1 % num2;
                    break;
                default:
                    throw invalid_argument("invalid operator");
                    break;
            }
            number_stack.push(result);
        }
        else{
            int num = stoi(str);
            number_stack.push(num);
        }
    }
    return number_stack.top();
}