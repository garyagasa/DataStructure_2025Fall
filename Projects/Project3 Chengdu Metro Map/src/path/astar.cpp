#include "../graph/graph.h"
#include "../graph/ret_format.h"
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <cmath>
#include <algorithm>

PathResult astar_shortest_path(Graph& graph, const std::string& start, const std::string& end) {
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

    auto heuristic = [&](const Vertex* vp){
        // The heuristic function using euclidian distance is consistent, which means that :
        // h(n_1) <= h(n_2) + distance(n_1, n_2). In A*, this means that we don't need to care about the nodes
        // that have been poped out of the fringe, whose colors == 2.
        Vertex* end_p = graph.getVertex(end);
        return sqrt((vp->x - end_p->x) * (vp->x - end_p->x) + (vp->y - end_p->y) * (vp->y - end_p->y));
    };
    
    auto cmp = [&](const Vertex* vp1, const Vertex* vp2){
        // return true if vp1 should be later
        return vp1->distance + heuristic(vp1) > vp2->distance + heuristic(vp2);
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
            
            // The heuristic function is consistent
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