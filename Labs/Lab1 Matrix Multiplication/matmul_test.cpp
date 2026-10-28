#include"matmul.h"
#include"matmul_pro.h"

void print_matrix(vector<vector<int>>& m){
    int num_row = m.size();
    int num_col = m[0].size();
    for(int i = 0; i < num_row; i++){
        cout << "|\t";
        for(int j = 0; j < num_col; j++){
            cout << m[i][j] << "\t";
        }
        cout << "|" << endl;
    }
    cout << endl;
}

// bruteforce algorithm testing
void matrix_mul_test_print_bf(vector<vector<int>>& m1, vector<vector<int>>& m2){
    cout << "start testing..." << endl << "m1=" << endl;
    print_matrix(m1);
    cout << "m2=" << endl;
    print_matrix(m2);
    cout << "m1 @ m2=" <<endl;
    vector<vector<int>> m = matmul_bruteforce(m1, m2);
    print_matrix(m);
    cout << "end testing" << endl;
}

// other algorithm(in "matmul.h") testing
void matrix_mul_test_print(vector<vector<int>>& m1, vector<vector<int>>& m2, bool is_strassen, bool is_padding=false){
    cout << "start testing..." << endl << "m1=" << endl;
    print_matrix(m1);
    cout << "m2=" << endl;
    print_matrix(m2);
    cout << "m1 @ m2=" <<endl;
    vector<vector<int>> m = is_strassen ? (is_padding ? matmul_strassen_padding(m1, m2) : matmul_strassen(m1, m2)) : matmul_ordinary(m1, m2);
    print_matrix(m);
    cout << "end testing" << endl;
}

// other algorithm(in "matmul_pro.h") testing
void matrix_mul_index_test_print(vector<vector<int>>& m1, vector<vector<int>>& m2, bool is_strassen, bool is_padding=false){
    cout << "start testing..." << endl << "m1=" << endl;
    print_matrix(m1);
    cout << "m2=" << endl;
    print_matrix(m2);
    cout << "m1 @ m2=" <<endl;
    vector<vector<int>> m = is_strassen ? (is_padding ? matmul_strassen_index_padding(m1, m2) : matmul_strassen_index(m1, m2)) : matmul_ordinary_index(m1, m2);
    print_matrix(m);
    cout << "end testing" << endl;
}

int main(){
    cout << "----------------------------test0, bruteforce-------------------------" << endl;
    vector<vector<int>> m11{vector<int>{1, 0, -4}, vector<int>{7, 0, 1}, vector<int>{2, 5, 8}};
    vector<vector<int>> m12{vector<int>{2, 1, 2}, vector<int>{1, 8, 5}, vector<int>{9, 0, 1}};
    matrix_mul_test_print_bf(m11, m12);

    cout << "----------------------------test1, ordinary---------------------------" << endl;
    vector<vector<int>> m1{vector<int>{1, 0, -4}, vector<int>{7, 0, 1}, vector<int>{2, 5, 8}};
    vector<vector<int>> m2{vector<int>{2, 1, 2}, vector<int>{1, 8, 5}, vector<int>{9, 0, 1}};
    matrix_mul_test_print(m1, m2, false);

    cout << "----------------------------test2, ordinary---------------------------" << endl;
    vector<vector<int>> m3{vector<int>{1, 0, 0}, vector<int>{0, 0, 1}, vector<int>{1, 1, 4}, vector<int>{5, 1, 4}};
    vector<vector<int>> m4{vector<int>{2, 1, 2, 5}, vector<int>{1, 8, 5, 1}, vector<int>{6, 3, 2, 4}};
    matrix_mul_test_print(m3, m4, false);

    cout << "----------------------------test3, strassen---------------------------" << endl;
    vector<vector<int>> m5{vector<int>{1, 0}, vector<int>{0, 1}};
    vector<vector<int>> m6{vector<int>{2, 1}, vector<int>{5, 1}};
    matrix_mul_test_print(m5, m6, true);

    cout << "----------------------------test4, strassen---------------------------" << endl;
    vector<vector<int>> m7{vector<int>{1, 0, 8, 1}, vector<int>{0, 1, 4, 5}, vector<int>{9, 5, 1, 4}, vector<int>{7, 5, 1, 2}};
    vector<vector<int>> m8{vector<int>{2, 1, 4, 1}, vector<int>{5, 1, 9, 9}, vector<int>{7, -2, 6, 5}, vector<int>{8, 9, 6, 4}};
    matrix_mul_test_print(m7, m8, true);

    cout << "----------------------------test5, strassen padding-------------------" << endl;
    vector<vector<int>> m9{vector<int>{1, 0, -4}, vector<int>{7, 0, 1}, vector<int>{2, 5, 8}};
    vector<vector<int>> m10{vector<int>{2, 1, 2, -1}, vector<int>{1, 8, 5, -9}, vector<int>{9, 0, 1, 4}};
    matrix_mul_test_print(m9, m10, true, true);

    cout << "----------------------------test6, ordinary(index)---------------------------" << endl;
    vector<vector<int>> m1_{vector<int>{1, 0, -4}, vector<int>{7, 0, 1}, vector<int>{2, 5, 8}};
    vector<vector<int>> m2_{vector<int>{2, 1, 2}, vector<int>{1, 8, 5}, vector<int>{9, 0, 1}};
    matrix_mul_index_test_print(m1_, m2_, false);

    cout << "----------------------------test7, ordinary(index)---------------------------" << endl;
    vector<vector<int>> m3_{vector<int>{1, 0, 0}, vector<int>{0, 0, 1}, vector<int>{1, 1, 4}, vector<int>{5, 1, 4}};
    vector<vector<int>> m4_{vector<int>{2, 1, 2, 5}, vector<int>{1, 8, 5, 1}, vector<int>{6, 3, 2, 4}};
    matrix_mul_index_test_print(m3_, m4_, false);

    cout << "----------------------------test8, strassen(index)---------------------------" << endl;
    vector<vector<int>> m5_{vector<int>{1, 0}, vector<int>{0, 1}};
    vector<vector<int>> m6_{vector<int>{2, 1}, vector<int>{5, 1}};
    matrix_mul_index_test_print(m5_, m6_, true);

    cout << "----------------------------test9, strassen(index)---------------------------" << endl;
    vector<vector<int>> m7_{vector<int>{1, 0, 8, 1}, vector<int>{0, 1, 4, 5}, vector<int>{9, 5, 1, 4}, vector<int>{7, 5, 1, 2}};
    vector<vector<int>> m8_{vector<int>{2, 1, 4, 1}, vector<int>{5, 1, 9, 9}, vector<int>{7, -2, 6, 5}, vector<int>{8, 9, 6, 4}};
    matrix_mul_index_test_print(m7_, m8_, true);

    cout << "---------------------------test10, strassen padding(index)-------------------" << endl;
    vector<vector<int>> m9_{vector<int>{1, 0, -4}, vector<int>{7, 0, 1}, vector<int>{2, 5, 8}};
    vector<vector<int>> m10_{vector<int>{2, 1, 2, -1}, vector<int>{1, 8, 5, -9}, vector<int>{9, 0, 1, 4}};
    matrix_mul_index_test_print(m9, m10, true, true);
    return 0;
}