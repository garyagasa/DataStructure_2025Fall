#pragma once
#include <string>
#include <vector>           
#include <unordered_map>   
#include <memory>           
#include <limits>           
#include <fstream>          
#include <sstream>          
#include <stdexcept>        
#include <iostream>         
#include <algorithm> 

class Vertex {
public:
    std::string id;
    std::unordered_map<std::string, double> adjacency;
    double x, y;
    
    double distance;
    std::string predecessor;
    int color;  // 0=white, 1=gray, 2=black
    int discovery_time, finish_time;
    
    Vertex(const std::string& vertex_id, double x_coord = 0, double y_coord = 0)
        : id(vertex_id), x(x_coord), y(y_coord), distance(std::numeric_limits<double>::infinity()),
          color(0), discovery_time(0), finish_time(0) {}
    
    void addNeighbor(const std::string& neighbor_id, double weight) {
        adjacency[neighbor_id] = weight;
    }
    
    double getWeight(const std::string& neighbor_id) const {
        auto it = adjacency.find(neighbor_id);
        return (it != adjacency.end()) ? it->second : std::numeric_limits<double>::infinity();
    }
    
    std::vector<std::string> getNeighbors() const {
        std::vector<std::string> neighbors;
        for (const auto& pair : adjacency) {
            neighbors.push_back(pair.first);
        }
        return neighbors;
    }
    
    void reset() {
        distance = std::numeric_limits<double>::infinity();
        predecessor = "";
        color = 0;
        discovery_time = 0;
        finish_time = 0;
    }
};

class Graph {
private:
    std::unordered_map<std::string, std::unique_ptr<Vertex>> vertices;
    int num_vertices;

public:
    Graph() : num_vertices(0) {}
    
    Graph(const Graph&) = delete;
    Graph& operator=(const Graph&) = delete;
    
    Graph(Graph&&) = default;
    Graph& operator=(Graph&&) = default;
    
    ~Graph() = default;
    
    void addVertex(const std::string& vertex_id, double x = 0, double y = 0) {
        if (vertices.find(vertex_id) == vertices.end()) {
            vertices[vertex_id] = std::make_unique<Vertex>(vertex_id, x, y);
            num_vertices++;
        }
    }
    
    void addEdge(const std::string& from, const std::string& to, double weight) {
        if (vertices.find(from) == vertices.end()) {
            addVertex(from);
        }
        if (vertices.find(to) == vertices.end()) {
            addVertex(to);
        }
        
        vertices[from]->addNeighbor(to, weight);
    }
    
    bool hasVertex(const std::string& vertex_id) const {
        return vertices.find(vertex_id) != vertices.end();
    }
    
    Vertex* getVertex(const std::string& vertex_id) {
        auto it = vertices.find(vertex_id);
        return (it != vertices.end()) ? it->second.get() : nullptr;
    }
    
    std::vector<std::string> getAllVertices() const {
        std::vector<std::string> vertex_list;
        for (const auto& pair : vertices) {
            vertex_list.push_back(pair.first);
        }
        return vertex_list;
    }
    
    std::vector<std::pair<std::pair<std::string, std::string>, double>> getAllEdges() const {
        std::vector<std::pair<std::pair<std::string, std::string>, double>> edges;
        for (const auto& vertex_pair : vertices) {
            const std::string& from = vertex_pair.first;
            const Vertex* vertex = vertex_pair.second.get();
            for (const auto& edge_pair : vertex->adjacency) {
                const std::string& to = edge_pair.first;
                double weight = edge_pair.second;
                edges.push_back({{from, to}, weight});
            }
        }
        return edges;
    }
    
    int getVertexCount() const { 
        return num_vertices; 
    }
    
    void clear() {
        vertices.clear();
        num_vertices = 0;
    }

    void reset(){
        auto vertices = getAllVertices();
        for (const auto& vertex : vertices) {
            getVertex(vertex)->reset();
        }
    }
    
    // Load data from files
    static Graph loadFromFiles(const std::string& edge_file, const std::string& vertex_file) {
        Graph graph;
        
        /**
         * ==================================================================================
         * ================================= Vertexes =======================================
         * ==================================================================================
         */

        std::ifstream vertex_stream(vertex_file);
        if (!vertex_stream.is_open()) {
            throw std::runtime_error("Cannot open vertex file: " + vertex_file);
        }
        
        std::vector<std::pair<double, double>> vertex_coords;
        std::string line;
        while (std::getline(vertex_stream, line)) {
            if (line.empty()) continue;
            
            // 简单解析 (x, y) 格式
            size_t comma_pos = line.find(',');
            if (comma_pos != std::string::npos) {
                // 移除括号和空格
                std::string x_str = line.substr(1, comma_pos - 1);
                std::string y_str = line.substr(comma_pos + 1);
                y_str = y_str.substr(0, y_str.find(')'));
                
                double x = std::stod(x_str);
                double y = std::stod(y_str);
                vertex_coords.push_back({x, y});
            }
        }
        vertex_stream.close();
        
        // 生成顶点名称
        std::string point_names;
        int num_vertices = vertex_coords.size();
        if (num_vertices <= 26) {
            for (int i = 0; i < num_vertices; i++) {
                point_names += char('A' + i);
            }
        } else if (num_vertices <= 52) {
            for (int i = 0; i < 26; i++) {
                point_names += char('A' + i);
            }
            for (int i = 0; i < num_vertices - 26; i++) {
                point_names += char('a' + i);
            }
        } else {
            throw std::runtime_error("Too many vertices (max 52)");
        }
        
        // 添加顶点
        for (size_t i = 0; i < vertex_coords.size(); i++) {
            std::string vertex_id(1, point_names[i]);
            graph.addVertex(vertex_id, vertex_coords[i].first, vertex_coords[i].second);
        }
        
        /**
         * ==================================================================================
         * ================================= Edges ==========================================
         * ==================================================================================
         */
        std::ifstream edge_stream(edge_file);
        if (!edge_stream.is_open()) {
            throw std::runtime_error("Cannot open edge file: " + edge_file);
        }
        
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
};