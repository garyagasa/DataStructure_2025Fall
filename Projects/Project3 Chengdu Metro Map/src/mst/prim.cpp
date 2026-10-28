#include "../graph/graph.h"
#include "../graph/ret_format.h"
#include "../graph/utils.h"
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>

typedef std::pair<std::pair<std::string, std::string>, double> Edge;

MSTResult prim_mst(Graph& graph, std::string start_vertex) {
    int num_vertices = graph.getVertexCount();
    // v_states: 0 for unvisited, 1 for visited
    std::vector<int> v_states(num_vertices, 0);

    auto cmp = [](Edge e1, Edge e2) -> bool{
        return e1.second > e2.second;
    };

    // Priority Queue to sort the edge in the order of the length(ascending)
    std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> pq(cmp);

    MSTResult ret;
    ret.success = false;
    ret.total_weight = 0;
    
    // Visit the first vertex(choose anywhere you like)
    Vertex* v = graph.getVertex(start_vertex);
    for(auto [n, d] : v->adjacency){
        pq.emplace(std::make_pair(start_vertex, n), d);
    }
    v_states[string2index(start_vertex)] = 1;

    while(!pq.empty() && ret.edges.size() < num_vertices - 1){
        Edge e_poped = pq.top();
        pq.pop();

        int neighbor_index = string2index(e_poped.first.second);
        if(v_states[neighbor_index] == 1){
            continue;
        }
        v_states[neighbor_index] = 1;
        Vertex* v = graph.getVertex(e_poped.first.second);
        for(auto [n, d] : v->adjacency){
            if(v_states[string2index(n)] == 0)
                pq.emplace(std::make_pair(e_poped.first.second, n), d);
        }
        ret.edges.emplace_back(e_poped.first.first, e_poped.first.second);
        ret.total_weight += e_poped.second;
    }

    if(ret.edges.size() == num_vertices - 1){
        ret.success = true;
    }

    return ret;
}