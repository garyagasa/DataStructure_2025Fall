#include "postfix_cal.h"

void cal_test(vector<string> tokens, int correct_ans, int index=0){
    cout << "Test " << index <<":"<< endl;
    
    for(string s : tokens){
        cout << s << " ";
    }
    cout << endl;
    int result = postfix_cal(tokens);
    cout << "result = " << result << endl;
    if(result == correct_ans){
        cout << "-----------Test " << index << " passed------------" << endl;
    }
    else{
        cout << "~~~~~~~~~~~Test " << index << " failed!!!~~~~~~~~~" << endl;
    }
}

int main(){
    // Test 1
    cal_test(vector<string>{"6", "4", "+", "7", "2", "-", "/"}, 2, 1);
    // Test 2
    cal_test(vector<string>{"6", "7", "*", "5", "8", "+", "%"}, 3, 2);
    // Test 3
    cal_test(vector<string>{"1", "3", "+", "2", "4", "+", "*", "6", "-", "8", "2", "-", "/"}, 3, 3);
    return 0;
}