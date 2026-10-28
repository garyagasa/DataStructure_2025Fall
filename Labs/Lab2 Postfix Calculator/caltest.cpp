#include "calculator.h"

void cal_test(string expression, int correct_result, int index=0){
    cout << "Test " << index << ":" << endl;
    cout << expression << " = " << cal(expression) << endl;
    cout << (cal(expression) == correct_result ? "True" : "False") << endl << "-------------------------------------" << endl; 
}

int main(){
    // Test 1
    cal_test("4+8*2", 20, 1);
    // Test 2
    cal_test("1 * 1 * 4 * 5 * 1 * 4", 80, 2);
    // Test 3
    cal_test("[(4+3-1)/(7%5)-4]*10/(2-5+8)", -2, 3);
    return 0;
}