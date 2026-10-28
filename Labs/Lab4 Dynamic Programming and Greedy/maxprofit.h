#pragma once
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include "action.h"


int max_profit(std::vector<Action>& actions, int total_time, std::vector<std::pair<Action, int>>& result){
    /**
     * Args:
     *  - vector<Action> actions:
     *      vectors of "n" actions, each element in the actions is an "Action with compoenent (t_j, p_j, d_j, index, info), where:
     *          "t_j" is the time that the j th element will spend
     *          "p_j" is the profit that the j th element will make
     *          "d_j" is the deadline of the j th element
     *          "info" is the string that represent the information of the action
     *      "t_j", "d_j" are in the range of [0, total_time]
     *  - max_time:
     *      The time we can take.The start time of ths story is "0" and ends at the time "total_time"
     *  - result:
     *      vector to return how to get the max_profit and the end time of each action, in the format of (<a_i1, j_i1>, <a_i2, j_i2>, ..., <a_ik, j_ik>)
     *      where "a_im" here represents the m th action that we ought to take
     * Return:
     *  - max_profit_num:
     *      the max_profit we can earn
     */
    int n = actions.size();
    std::sort(actions.begin(), actions.end(), action_compare_ddl);      // ascending sort according to ddl, get(a_1, a_2, ..., a_n)
    
    /**
     * Dynamic Programming profit matrix, profit_matrix[i][j] means the subproblem that:
     *  - We can only choose the action from "a_1" to "a_i"
     *  - The problem start at 0 and end at "j"
     */
    int profit_matrix[n + 1][total_time + 1];
    /**
     * Dynamic Programming record matrix, the element(i, j):
     *  - =0, if we choose to add a new "a_i", the early problem should be (i - 1, j - a_i.time):
     *    profit_matrix[i][j] = profit_matrix[i - 1][j - a_i.time] + a_i.profit
     *      **Notice that we can not add an action after its deadline**
     *  - =1, if we choose not to add a new "a_i", end at j:
     *    profit_matrix[i][j] = profit_matrix[i - 1][j]
     *  - =2, if we choose not to add a new "a_i", end before j:
     *    profit_matrix[i][j] = profit_matrix[i][j - 1]
     */
    int record_matrix[n + 1][total_time + 1];

    for(int i = 0; i < n + 1; i++){
        profit_matrix[i][0] = 0;
    }

    for(int j = 0; j < total_time + 1; j++){
        profit_matrix[0][j] = 0;
    }

    // DP to get the max_profit_num
    for(int i = 1; i < n + 1; i++){
        for(int j = 1; j < total_time + 1; j++){
            /*if the time is after the deadline of the action a_i, we can only choose the 1/2 case*/
            if(actions[i - 1].deadline < j){
                // case1
                if(profit_matrix[i - 1][j] > profit_matrix[i][j - 1]){
                    profit_matrix[i][j] = profit_matrix[i - 1][j];
                    record_matrix[i][j] = 1;
                }
                // case2
                else{
                    profit_matrix[i][j] = profit_matrix[i][j - 1];
                    record_matrix[i][j] = 2;
                }
                continue;
            }

            /*if the time is not after the deadline*/
            int profit0 = 0;
            if(j >= actions[i - 1].time){
                profit0 = profit_matrix[i - 1][j - actions[i - 1].time] + actions[i - 1].profit;
            }
            int profit1 = profit_matrix[i - 1][j];
            int profit2 = profit_matrix[i][j - 1];

            // case 0
            if(profit0 > profit1 && profit0 > profit2){
                profit_matrix[i][j] = profit0;
                record_matrix[i][j] = 0;
            }
            // case 1
            else if(profit1 > profit2){
                profit_matrix[i][j] = profit1;
                record_matrix[i][j] = 1;
            }
            // case 2
            else{
                profit_matrix[i][j] = profit2;
                record_matrix[i][j] = 2; 
            }
        }
    }

    int max_profit_num = profit_matrix[n][total_time];

    // Rebuild the process
    int i_p = n, j_p = total_time;
    while(i_p != 0 && j_p != 0){
        int case_choice = record_matrix[i_p][j_p];
        /*case 0*/
        if(case_choice == 0){
            result.emplace_back(actions[i_p - 1], j_p);
            j_p = j_p - actions[i_p - 1].time;
            i_p = i_p - 1;
        }
        /*case 1*/
        else if(case_choice == 1){
            i_p = i_p - 1;
        }
        /*case 2*/
        else{
            j_p = j_p - 1;
        }
    }

    std::reverse(result.begin(), result.end());

    return max_profit_num;
}