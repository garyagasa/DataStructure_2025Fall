#include "../graph/graph_matrix.h"
#include "../graph/ret_format.h"
#include "../graph/utils.h"
#include <vector>
#include <algorithm>
using namespace std;

FloydWarshallResult floyd_warshall_all_pairs(Graph_Matrix& graph) {
    FloydWarshallResult result;
    if(!graph.is_run_floyd){
        graph.run_floyd();
    }
    result = graph.result;
    return result;
}

FloydWarshallResult mat_mul_all_pairs(Graph_Matrix& graph){
    FloydWarshallResult result;
    if(!graph.is_run_matmul){
        graph.run_matmul();
    }
    result = graph.result;
    return result;
}

PathResult floyd_warshall_get_path(const FloydWarshallResult& floyd_result, 
                                  const std::string& start, const std::string& end) {
    PathResult p;
    int start_idx = string2index(start);
    int end_idx = string2index(end);

    std::vector<std::vector<int>> pi = floyd_result.next_vertex;
    p.distance = floyd_result.distances[start_idx][end_idx];
    p.found = !floyd_result.has_negative_cycle;

    int current_end = end_idx;
    while(current_end != start_idx){
        p.path.push_back(index2string(current_end));
        current_end = pi[start_idx][current_end];
    }
    p.path.push_back(start);
    std::reverse(p.path.begin(), p.path.end());

    return p;
}

PathResult matmul_get_path(const FloydWarshallResult& matmul_result,
                        const std::string& start, const std::string& end){
    PathResult p;
    int start_idx = string2index(start);
    int end_idx = string2index(end);

    std::vector<std::vector<int>> pi = matmul_result.next_vertex;
    p.distance = matmul_result.distances[start_idx][end_idx];
    p.found = !matmul_result.has_negative_cycle;

    int current_end = end_idx;
    while(current_end != start_idx){
        p.path.push_back(index2string(current_end));
        current_end = pi[start_idx][current_end];
    }
    p.path.push_back(start);
    std::reverse(p.path.begin(), p.path.end());

    return p;
}