#pragma once
#include <cstdio>
#include "string"

class Action{
    /**Class action:
     * - time(int)              # range: [0, total_time]
     * - profit(double)
     * - deadline(int)
     * - tag(int)                                              
     * - string(information)    # range: [0, total_time]
    */
    public:
        int time;
        double profit;
        int deadline;
        std::string information;

        /*Constructor*/
        Action(int t, double p, int d, std::string action_info=""){
            time = t;
            profit = p;
            deadline = d;
            information = action_info;          
        }
};

/*Comparator of two actions, comparing according to their deadlines*/
bool action_compare_ddl(const Action& a1, const Action& a2){
    // ddl ascendinig
    return a1.deadline < a2.deadline;
}