#include <cstdio>
#include <iostream>
#include <string>
#include <stack>

using namespace std;

void towers(int n, string A, string B, string C){
    if(n == 1){
        std::cout << A << "->" << C << std::endl;
    }
    else{
        towers(n - 1, A, C, B);
        std::cout << A << "->" << C << std::endl;
        towers(n - 1, B, A, C);
    }
}

class state{
    public:
    int n;
    int time; // 0, 1, 2
    string A;
    string B;
    string C;
    state(int n, int time=0, string A="", string B="", string C=""){
        this->n = n;
        this->time = 0;
        this->A = A;
        this->B = B;
        this->C = C;
    }
};

void towers_norecur(int n, string A, string B, string C){
    stack<state> fringe;

    state init_state(n, 0, A, B, C);
    fringe.push(init_state);

    while(!fringe.empty()){
        if(fringe.top().n == 1){
            cout << fringe.top().A << "->" << fringe.top().C << endl;
            fringe.pop();
            continue;
        }
        
        switch (fringe.top().time){
        case 0:
            fringe.top().time++;
            fringe.emplace(fringe.top().n - 1, 0, fringe.top().A, fringe.top().C, fringe.top().B);
            break;
        case 1:
            fringe.top().time++;
            cout << fringe.top().A << "->" << fringe.top().C << endl;
            fringe.emplace(fringe.top().n - 1, 0, fringe.top().B, fringe.top().A, fringe.top().C);
            break;
        default:
            fringe.pop();
            break;
        }
        
    }
}

int main(){
    towers(3, "fuck", "shit", "bitch");
    cout << "-----------------------------------" << endl;
    towers_norecur(3, "fuck", "shit", "bitch");
    return 0;
}