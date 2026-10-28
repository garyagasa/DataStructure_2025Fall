#pragma once
#include <cstdio>
#include <stdexcept>
#include <string>
#include "graph.h" 

int string2index(std::string str);

std::string index2string(int idx);

class Disjoint_Set{
    public:
    std::vector<int> set_index;
    std::vector<int> rank;
    
    Disjoint_Set(int num_vertices){
        set_index = std::vector<int>(num_vertices);
        rank = std::vector<int>(num_vertices, 0);
        
        for(int i = 0; i < num_vertices; i++){
            set_index[i] = i;
        }
    }

    int find_set(int index){
        if(set_index[index] == index){
            return index;
        }
        // Path Compression
        set_index[index] = find_set(set_index[index]);
        return set_index[index];
    }

    void union_set(int idx1, int idx2){
        int root1 = find_set(idx1);
        int root2 = find_set(idx2);

        if(root1 == root2){
            return;
        }

        if(rank[root1] > rank[root2]){
            set_index[root2] = root1;
        }
        else if(rank[root1] < rank[root2]){
            set_index[root1] = root2;
        }
        else{
            set_index[root2] = root1;
            rank[root1] += 1;
        }
    }
};