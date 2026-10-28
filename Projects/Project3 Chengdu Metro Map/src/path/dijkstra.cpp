#include "../graph/graph.h"
#include "../graph/ret_format.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>

PathResult dijkstra_shortest_path(Graph& graph, const std::string& start, const std::string& end) {
    std::vector<std::string> path;
    double dist = 0;
    bool is_found = false;

    // recurse back and rebuild the path
    auto rebuild_path = [&](){
        std::string current_id = end;
        std::vector<std::string> ret;
        
        while(current_id != start){
            ret.push_back(current_id);
            current_id = graph.getVertex(current_id)->predecessor;
        }

        ret.push_back(start);
        std::reverse(ret.begin(), ret.end());
        return ret;
    };

    auto cmp = [](const Vertex* vp1, const Vertex* vp2){
        // return true if vp1 should be later
        return vp1->distance > vp2->distance;
    };
    
    std::priority_queue<Vertex*, std::vector<Vertex*>, decltype(cmp)> fringe(cmp);
    // The priority queue of STL doesn't support the "decrease-key" operation, so we need to repeat the IN-FRINGE operation,
    // thus may causing multiple occurence of the same vertex in the fringe. We also need to prevent repeating DE-FRINGE the 
    // same vertex for numerous times when we pop a vertex out of the fringe.

    graph.reset();
    
    Vertex* start_node_ptr = graph.getVertex(start);
    start_node_ptr->distance = 0;
    start_node_ptr->color= 1;
    fringe.push(start_node_ptr);

    while(!fringe.empty()){
        Vertex* poped_node_ptr = fringe.top();
        fringe.pop();

        // Handle the problem of repeating DE-FRINGE
        if(poped_node_ptr->color == 2){
            continue;
        }

        poped_node_ptr->color = 2;

        // Find the end point
        if(poped_node_ptr->id == end){
            path = rebuild_path();
            dist = poped_node_ptr->distance;
            is_found = true;
            break;
        }

        for(auto& neighbor : poped_node_ptr->adjacency){
            Vertex* neighbor_ptr = graph.getVertex(neighbor.first);
            double way_dist = neighbor.second;
            
            if(neighbor_ptr->color != 2){
                // Relaxation Operation
                if(neighbor_ptr->distance > (poped_node_ptr->distance + way_dist)){
                    neighbor_ptr->distance = poped_node_ptr->distance + way_dist;
                    neighbor_ptr->predecessor = poped_node_ptr->id;
                }
                neighbor_ptr->color = 1;
                fringe.push(neighbor_ptr);
            }
        }

    }

    return PathResult(path, dist, is_found);
}

OneToAllResult dijkstra_one_to_all(Graph& graph, const std::string& start) {
    OneToAllResult result;
    result.source = start;

    // recurse back and rebuild the path
    auto rebuild_path = [&](const std::string& end){
        std::string current_id = end;
        std::vector<std::string> ret;
        
        while(current_id != start){
            ret.push_back(current_id);
            current_id = graph.getVertex(current_id)->predecessor;
        }

        ret.push_back(start);
        std::reverse(ret.begin(), ret.end());
        return ret;
    };

    auto cmp = [](const Vertex* vp1, const Vertex* vp2){
        // return true if vp1 should be later
        return vp1->distance > vp2->distance;
    };
    
    std::priority_queue<Vertex*, std::vector<Vertex*>, decltype(cmp)> fringe(cmp);

    graph.reset();
    
    Vertex* start_node_ptr = graph.getVertex(start);
    start_node_ptr->distance = 0;
    start_node_ptr->color= 1;
    fringe.push(start_node_ptr);

    while(!fringe.empty()){
        Vertex* poped_node_ptr = fringe.top();
        fringe.pop();

        // Handle the problem of repeating DE-FRINGE
        if(poped_node_ptr->color == 2){
            continue;
        }

        poped_node_ptr->color = 2;

        for(auto& neighbor : poped_node_ptr->adjacency){
            Vertex* neighbor_ptr = graph.getVertex(neighbor.first);
            double way_dist = neighbor.second;
            
            if(neighbor_ptr->color != 2){
                // Relaxation Operation
                if(neighbor_ptr->distance > (poped_node_ptr->distance + way_dist)){
                    neighbor_ptr->distance = poped_node_ptr->distance + way_dist;
                    neighbor_ptr->predecessor = poped_node_ptr->id;
                }
            
                neighbor_ptr->color = 1;
                fringe.push(neighbor_ptr);
            }
        }

    }
    
    auto vertices = graph.getAllVertices();
    for (const auto& vertex : vertices) {
        if (vertex != start) {
            result.results[vertex] = PathResult(rebuild_path(vertex), graph.getVertex(vertex)->distance, true);
        }
    }
    
    return result;
}