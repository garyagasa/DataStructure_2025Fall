#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <limits>
#include <fstream>
#include <sstream>
#include "../graph/utils.h"
#include "ret_format.h"

class Graph_Matrix {
private:
    // std::unordered_map<std::string, std::unique_ptr<Vertex>> vertices;
    int num_vertices = 52;
    // adjacency matrix
public:
    std::vector<std::vector<double>> adj_matrix;
    FloydWarshallResult result;

    bool is_run_matmul = false;
    bool is_run_floyd = false;

    Graph_Matrix(){
        adj_matrix.assign(num_vertices, std::vector<double>(num_vertices, std::numeric_limits<double>::infinity()));
        for(int i = 0; i < num_vertices; i++){
            adj_matrix[i][i] = 0;
        }
    }
    
    Graph_Matrix(const Graph_Matrix&) = delete;
    Graph_Matrix& operator=(const Graph_Matrix&) = delete;
    
    Graph_Matrix(Graph_Matrix&&) = default;
    Graph_Matrix& operator=(Graph_Matrix&&) = default;
    
    ~Graph_Matrix() = default;
    
    void addEdge(const std::string& from, const std::string& to, double weight) {
        int from_idx = string2index(from);
        int to_idx = string2index(to);

        adj_matrix[from_idx][to_idx] = weight;
    }
    
    std::vector<std::pair<std::pair<std::string, std::string>, double>> getAllEdges() const {
        std::vector<std::pair<std::pair<std::string, std::string>, double>> edges;
        for(int i = 0; i < num_vertices; i++){
            std::string start = index2string(i);
            for(int j = 0; j < num_vertices; j++){
                std::string end = index2string(j);
                edges.push_back({{start, end}, adj_matrix[i][j]});
            }
        }
        return edges;
    }
    
    int getVertexCount() const { 
        return num_vertices; 
    }
    
    void clear() {
        adj_matrix.clear();
        num_vertices = 0;
    }

    void reset() {
        is_run_floyd = false;
        is_run_matmul = false;
        result = FloydWarshallResult();
    }
    
    // Load data from files
    static Graph_Matrix loadFromFiles(const std::string& edge_file) {
        Graph_Matrix graph;        
        /**
         * ==================================================================================
         * ================================= Edges ==========================================
         * ==================================================================================
         */
        std::ifstream edge_stream(edge_file);
        if (!edge_stream.is_open()) {
            throw std::runtime_error("Cannot open edge file: " + edge_file);
        }
        
        std::string line;
        while (std::getline(edge_stream, line)) {
            if (line.empty()) continue;
            
            std::istringstream iss(line);
            std::string from, to;
            double weight;
            
            if (iss >> from >> to >> weight) {
                graph.addEdge(from, to, weight);
                graph.addEdge(to, from, weight);  
            }
        }
        edge_stream.close();
        
        return graph;
    }

    void result_processing(){
        // vertex order
        for(int i = 0; i < num_vertices; ++i) {
            result.vertex_order.push_back(index2string(i));
        }
        // if there is a negative cycle
        result.has_negative_cycle = false;
        for(int i = 0; i < num_vertices; i++){
            if(result.distances[i][i] < 0){
                result.has_negative_cycle = true;
            }
        }
    }

    class d_and_pi{
        public:
        std::vector<std::vector<double>> d;
        std::vector<std::vector<int>> pi;

        d_and_pi(int num_vertices){
            d.assign(num_vertices, std::vector<double>(num_vertices, std::numeric_limits<double>::infinity()));
            pi.assign(num_vertices, std::vector<int>(num_vertices, -1));
        }
    };

    FloydWarshallResult run_matmul(){
        reset();
        is_run_matmul = true;

        /* Initialize dp_0*/
        d_and_pi dp_0(num_vertices);
        for(int i = 0; i < num_vertices; i++){
            dp_0.d[i][i] = 0;
            dp_0.pi[i][i] = -1;
            for(int j = 0; j < num_vertices; j++){
                if(i == j) continue;
                if(adj_matrix[i][j] != std::numeric_limits<double>::infinity()){
                    dp_0.d[i][j] = adj_matrix[i][j];
                    dp_0.pi[i][j] = i;  
                }
            }
        }

        d_and_pi current_dp = dp_0;
        // Update for num_vertices - 1 times
        for(int m = 1; m < num_vertices; m++){
            current_dp = matmul_extend(current_dp);
        }

        result.distances = current_dp.d;
        result.next_vertex = current_dp.pi;
        result_processing();

        return result;
    }

    d_and_pi matmul_extend(d_and_pi& dp_i){
        d_and_pi dp_i1(dp_i);
        
        for(int i = 0; i < num_vertices; i++){
            for(int j = 0; j < num_vertices; j++){
                // Update the shortest path value at position (i, j)
                // Try all possible intermediate nodes
                double dis_current = dp_i1.d[i][j];
                for(int k = 0; k < num_vertices; k++){
                    // Dynamic Programming
                    double dis_newtrial = dp_i.d[i][k] + adj_matrix[k][j];
                    if(dis_newtrial < dis_current){
                        // Update
                        dis_current = dis_newtrial;
                        dp_i1.d[i][j] = dis_current;
                        dp_i1.pi[i][j] = k;
                    }
                }
            }
        }
        return dp_i1;
    }

    FloydWarshallResult run_floyd(){
        reset();
        is_run_floyd = true;
        
        // Initialize dp_-1
        d_and_pi dp_minus1(num_vertices);

        for(int i = 0; i < num_vertices; i++){
            dp_minus1.d[i][i] = 0;
            dp_minus1.pi[i][i] = -1;
            for(int j = 0; j < num_vertices; j++){
                if(i == j) continue;
                dp_minus1.d[i][j] = adj_matrix[i][j];
                if(adj_matrix[i][j] != std::numeric_limits<double>::infinity()){
                    dp_minus1.pi[i][j] = i;
                }
            }
        }

        d_and_pi current_dp = dp_minus1;
        for(int k = 0; k < num_vertices; k++){
            current_dp = fw_extend(current_dp, k);
        }
        
        result.distances = current_dp.d;
        result.next_vertex = current_dp.pi;
        result_processing();
        return result;
    }

    d_and_pi fw_extend(d_and_pi& dp_i, int k){
        // we allow the vertex k to used for the first time
        d_and_pi dp_i1 = dp_i;

        for(int i = 0; i < num_vertices; i++){
            for(int j = 0; j < num_vertices; j++){
                // Dynamic Programming
                double dis_newtrial = dp_i.d[i][k] + dp_i.d[k][j];
                if(dis_newtrial < dp_i1.d[i][j]){
                    // Update
                    dp_i1.d[i][j] = dis_newtrial;
                    dp_i1.pi[i][j] = dp_i.pi[k][j];
                }
            }
        }

        return dp_i1;
    }
};