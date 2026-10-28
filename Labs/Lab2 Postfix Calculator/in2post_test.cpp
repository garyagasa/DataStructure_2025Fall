#include "in2post.h"
#include "string2vec.h"

void in2post_test(vector<string> tokens, int index=0){
    cout << "Test " << index <<":"<< endl;
    cout << "Infix: ";
    for(string s : tokens){
        cout << s << " ";
    }
    cout << endl;

    cout << "Postfix: ";
    auto result = in2post(tokens);
    for(string s : result){
        cout << s << " ";
    }
    cout << endl;
    cout << "--------------------------------------" << endl;
}

int main(){
    // Test 1
    in2post_test(vector<string>{"(", "6", "+", "2", ")", "/", "4"}, 1);
    // Test 2
    in2post_test(vector<string>{"[", "(", "1", "+", "3", ")", "*", "(", "2", "+", "4", ")", "-", "6", "]"}, 2);
    // Test 3
    in2post_test(string2vec("(1+9)*(8+9)/(6-4)"), 3);
    // Test 4
    in2post_test(string2vec("[(1+3)*(2+4)-6]/(9-7)%2"), 4);
    // Test 5
    in2post_test(string2vec("5-2+1"), 5);
    return 0;
}