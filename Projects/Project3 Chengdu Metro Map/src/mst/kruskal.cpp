#include "../graph/graph.h"
#include "../graph/ret_format.h"
#include "../graph/utils.h"
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>

typedef std::pair<std::pair<std::string, std::string>, double> Edge;

MSTResult kruskal_mst(Graph& graph) {
    int num_vertices = graph.getVertexCount();
    std::vector<Edge> all_edges = graph.getAllEdges();

    auto cmp = [](Edge e1, Edge e2) -> bool{
        return e1.second > e2.second;
    };

    // Priority Queue to sort the edge in the order of the length(ascending)
    std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> pq(cmp);
    for(auto e : all_edges){
        pq.push(e);
    }
    // Disjoint set of the vertices
    Disjoint_Set ds(num_vertices);
    MSTResult ret;
    ret.success = false;
    ret.total_weight = 0;
    
    while(!pq.empty() && ret.edges.size() < num_vertices - 1){
        Edge e_poped = pq.top();
        pq.pop();

        int set_index1 = ds.find_set(string2index(e_poped.first.first));
        int set_index2 = ds.find_set(string2index(e_poped.first.second));
        if(set_index1 == set_index2){
            continue;
        }
        ds.union_set(set_index1, set_index2);
        ret.edges.emplace_back(e_poped.first.first, e_poped.first.second);
        ret.total_weight += e_poped.second;
    }

    if(ret.edges.size() == num_vertices - 1){
        ret.success = true;
    }

    return ret;
}