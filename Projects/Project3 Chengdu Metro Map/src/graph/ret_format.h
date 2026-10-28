#pragma once
#include <cstdio>
#include <string>
#include <map>
#include <vector>

struct PathResult {
    std::vector<std::string> path;
    double distance;
    bool found;
    
    PathResult() : distance(0.0), found(false) {}
    PathResult(const std::vector<std::string>& p, double d, bool f) 
        : path(p), distance(d), found(f) {}
};

struct MSTResult {
    std::vector<std::pair<std::string, std::string>> edges;
    double total_weight;
    bool success;
    
    MSTResult() : total_weight(0.0), success(false) {}
    MSTResult(const std::vector<std::pair<std::string, std::string>>& e, double w, bool s)
        : edges(e), total_weight(w), success(s) {}
};

struct OneToAllResult {
    std::map<std::string, PathResult> results;
    std::string source;
    
    OneToAllResult() {}
    OneToAllResult(const std::map<std::string, PathResult>& r, const std::string& s)
        : results(r), source(s) {}
};

struct FloydWarshallResult {
    std::vector<std::vector<double>> distances;
    std::vector<std::vector<int>> next_vertex;
    std::vector<std::string> vertex_order;
    bool has_negative_cycle;
    
    FloydWarshallResult() : has_negative_cycle(false) {}
};