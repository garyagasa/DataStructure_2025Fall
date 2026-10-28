#include <cstdio>
#include <iostream>
#include "vector"
#include "maxprofit.h"

void test_maxprofit(std::vector<Action> action_vec, int total_time){
    std::vector<std::pair<Action, int>> action_ret;
    int mp = max_profit(action_vec, total_time, action_ret);
    std::cout<< "================Start testing===================="<< std::endl;
    std::cout << "Max Profit =" << mp << std::endl;
    for(auto& action : action_ret){
        std::cout << action.first.information << " : " << std::endl;
        std::cout << "  start at: " << action.second - action.first.time << std::endl;
        std::cout << "  end at:   " << action.second << std::endl;
    }
    std::cout<< "================End testing======================"<< std::endl;
}

int main(){
    std::vector<Action> va1{Action(1, 1, 9, "brush teeth"),
                            Action(4, 2, 12, "play majiang"),
                            Action(1, 2, 24, "dating with girl friend"),
                            Action(2, 3, 12, "take classes"),
                            Action(5, 6, 12, "do math homework"),
                            Action(6, 10, 16, "train deep neural network"),
                            Action(4, 5, 11, "coding"),
                            Action(7, 6, 23, "sleep"),
                            Action(1, 2, 17, "play soccer")};
    test_maxprofit(va1, 24);
    
    std::vector<Action> va2{Action(3, 6, 4, "抗美援朝"),
                            Action(10, 1, 27, "无产阶级文化大革命"),
                            Action(30, 80, 70, "改革开放"),
                            Action(3, 2, 15, "三年自然灾害"),
                            Action(5, 9, 9, "第一个五年计划"),
                            Action(10, 25, 63, "构建社会主义和谐社会"),
                            Action(10, 15, 70, "中国特色社会主义进入新时代"),
                            Action(3, 5, 70, "抗击新冠疫情"),
                            Action(10, 20, 53, "贯彻落实三个代表重要思想"),
                            Action(5, 12, 70, "一国两制统一中国")};
    test_maxprofit(va2, 70);

    std::vector<Action> va3{Action(6, 10, 12, "备战小升初"),
                            Action(6, 12, 6, "幼儿园启蒙"),
                            Action(3, 20, 15, "冲刺中考"),
                            Action(3, 30, 18, "卷高考，考复旦"),
                            Action(10, 35, 30, "初中毕业，下海经商"),
                            Action(4, 25, 22, "保研推免"),
                            Action(3, 20, 25, "学硕毕业"),
                            Action(4, 25, 29, "博士毕业"),
                            Action(5, 30, 27, "直博毕业"),
                            Action(6, 10, 26, "女友分手"),
                            Action(3, 5, 35, "中年危机"),
                            Action(3, 5, 37, "非升即走"),
                            Action(3, 5, 30, "家里催婚"),
                            Action(5, 20, 40, "退休万岁")};
    test_maxprofit(va3, 40);
    return 0;
}