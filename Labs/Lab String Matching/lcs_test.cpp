#include <cstdio>
#include <iostream>
#include "lcs.h"

int main(){
    vector<string> s1({"a", "c", "g", "m", "v", "k", "t", "q"});
    vector<string> s2({"r", "a", "g", "v", "q", "W", "m"});
    vector<string> common = longset_common_subseqence(s1, s2);
    for(auto i : common){
        cout << i << " ";
    }
    cout << endl;
    return 0;
}