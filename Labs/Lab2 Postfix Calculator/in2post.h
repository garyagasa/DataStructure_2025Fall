#pragma once
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<set>
#include<stack>
#include<vector>
#include<string>
using namespace std;

set<string> operator_set({"+", "-", "*", "/", "%", "(", ")", "[", "]"});

vector<string> in2post(vector<string>& tokens) {
    vector<string> ret;
    stack<string> operator_stack;

    for(auto & str : tokens){
        // if it is an operator
        if(operator_set.count(str)){
            if(str == "(" || str == "["){
                operator_stack.push(str);
            }
            else if(str == ")"){
                while(!operator_stack.empty()){
                    string top_operator = operator_stack.top();
                    operator_stack.pop();
                    if(top_operator == "("){
                        break;
                    }
                    ret.push_back(top_operator);
                }
            }
            else if(str == "]"){
                while(!operator_stack.empty()){
                    string top_operator = operator_stack.top();
                    operator_stack.pop();
                    if(top_operator == "["){
                        break;
                    }
                    ret.push_back(top_operator);
                }
            }
            else if(str == "*" || str == "/" || str == "%"){
                if(operator_stack.empty()){
                    operator_stack.push(str);
                }
                else{
                    while(operator_stack.top() == "*" || operator_stack.top() == "/" || operator_stack.top() == "%"){
                        string top_operator = operator_stack.top();
                        operator_stack.pop();
                        ret.push_back(top_operator);
                        if(operator_stack.empty()){
                            break;
                        }
                    }
                    operator_stack.push(str);
                }
            }
            else if(str == "+" || str == "-"){
                if(operator_stack.empty()){
                    operator_stack.push(str);
                }
                else{
                    while(operator_stack.top() == "*" || operator_stack.top() == "/" || operator_stack.top() == "%" 
                        || operator_stack.top() == "+" || operator_stack.top() == "-"){
                        string top_operator = operator_stack.top();
                        operator_stack.pop();
                        ret.push_back(top_operator);
                        if(operator_stack.empty()){
                            break;
                        }
                    }
                    operator_stack.push(str);
                }
            }
        }
        // if it is a number
        else{
            ret.push_back(str);
        }
    }
    // empty the stack
    while(!operator_stack.empty()){
        string top_operator = operator_stack.top();
        operator_stack.pop();
        ret.push_back(top_operator);
    }
    return ret;
}