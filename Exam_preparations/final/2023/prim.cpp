#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct Point{
    double x;
    double y;
}Point;

double distance(Point a, Point b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double mst_cost(Point p_arr[], int num){
    auto edge_cmp = [&](pair<int, int> e_a_index, pair<int, int> e_b_index){
        auto e_a = make_pair(p_arr[e_a_index.first], p_arr[e_a_index.second]);
        auto e_b = make_pair(p_arr[e_b_index.first], p_arr[e_b_index.second]);
        return distance(e_a.first, e_a.second) > distance(e_b.first, e_b.second);
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(edge_cmp)> edge_fringe(edge_cmp);
    vector<bool> is_visited(num, false);
    int visited_num = 0;
    double ret = 0;
    
    for(int i = 1; i < num; i++){
        edge_fringe.emplace(0, i);
    }
    visited_num = 1;
    is_visited[0] = true;

    while(!edge_fringe.empty() && visited_num < num){
        auto e = edge_fringe.top();
        edge_fringe.pop();

        if(is_visited[e.second]){
            continue;
        }

        is_visited[e.second] = true;
        visited_num += 1;
        ret += distance(p_arr[e.first], p_arr[e.second]);

        for(int i = 0; i < num; i++){
            if(i == e.second) continue;
            if(is_visited[i] == false){
                edge_fringe.emplace(e.second, i);
            }
        }
    }

    return ret;
}

