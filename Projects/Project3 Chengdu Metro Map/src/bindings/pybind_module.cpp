#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <algorithm>

#include "../graph/ret_format.h"
#include "../graph/graph.h"
#include "../graph/graph_matrix.h"

#include "../path/dijkstra.h"
#include "../path/astar.h"
#include "../path/floyd_warshall.h"

#include "../mst/kruskal.h"
#include "../mst/prim.h"

namespace py = pybind11;

// pybind11模块定义
PYBIND11_MODULE(metro_core, m) {
    m.doc() = "Metro algorithms C++ implementation with pybind11";

    // 绑定结果结构
    py::class_<PathResult>(m, "PathResult")
        .def(py::init<>())
        .def(py::init<const std::vector<std::string>&, double, bool>())
        .def_readwrite("path", &PathResult::path)
        .def_readwrite("distance", &PathResult::distance)
        .def_readwrite("found", &PathResult::found)
        .def("__repr__", [](const PathResult& r) {
            return "<PathResult path=" + std::to_string(r.path.size()) + 
                   " nodes, distance=" + std::to_string(r.distance) + 
                   ", found=" + (r.found ? "True" : "False") + ">";
        });

    py::class_<MSTResult>(m, "MSTResult")
        .def(py::init<>())
        .def(py::init<const std::vector<std::pair<std::string, std::string>>&, double, bool>())
        .def_readwrite("edges", &MSTResult::edges)
        .def_readwrite("total_weight", &MSTResult::total_weight)
        .def_readwrite("success", &MSTResult::success)
        .def("__repr__", [](const MSTResult& r) {
            return "<MSTResult edges=" + std::to_string(r.edges.size()) + 
                   ", total_weight=" + std::to_string(r.total_weight) + 
                   ", success=" + (r.success ? "True" : "False") + ">";
        });

    py::class_<OneToAllResult>(m, "OneToAllResult")
        .def(py::init<>())
        .def(py::init<const std::map<std::string, PathResult>&, const std::string&>())
        .def_readwrite("results", &OneToAllResult::results)
        .def_readwrite("source", &OneToAllResult::source)
        .def("__repr__", [](const OneToAllResult& r) {
            return "<OneToAllResult source=" + r.source + 
                   ", targets=" + std::to_string(r.results.size()) + ">";
        });

    py::class_<FloydWarshallResult>(m, "FloydWarshallResult")
        .def(py::init<>())
        .def_readwrite("distances", &FloydWarshallResult::distances)
        .def_readwrite("next_vertex", &FloydWarshallResult::next_vertex)
        .def_readwrite("vertex_order", &FloydWarshallResult::vertex_order)
        .def_readwrite("has_negative_cycle", &FloydWarshallResult::has_negative_cycle)
        .def("__repr__", [](const FloydWarshallResult& r) {
            return "<FloydWarshallResult vertices=" + std::to_string(r.vertex_order.size()) + 
                   ", has_negative_cycle=" + (r.has_negative_cycle ? "True" : "False") + ">";
        });

    // Class Vertex
    py::class_<Vertex>(m, "Vertex")
        .def(py::init<const std::string&, double, double>(), 
             py::arg("vertex_id"), py::arg("x") = 0, py::arg("y") = 0)
        .def_readwrite("id", &Vertex::id)
        .def_readwrite("x", &Vertex::x)
        .def_readwrite("y", &Vertex::y)
        .def_readwrite("distance", &Vertex::distance)
        .def_readwrite("predecessor", &Vertex::predecessor)
        .def_readwrite("color", &Vertex::color)
        .def("addNeighbor", &Vertex::addNeighbor)
        .def("getWeight", &Vertex::getWeight)
        .def("getNeighbors", &Vertex::getNeighbors)
        .def("reset", &Vertex::reset)
        .def("__repr__", [](const Vertex& v) {
            return "<Vertex " + v.id + " at (" + std::to_string(v.x) + 
                   ", " + std::to_string(v.y) + ")>";
        });

    // Class Graph
    py::class_<Graph>(m, "Graph")
        .def(py::init<>())
        .def("add_vertex", &Graph::addVertex, 
             py::arg("vertex_id"), py::arg("x") = 0, py::arg("y") = 0)
        .def("add_edge", &Graph::addEdge)
        .def("has_vertex", &Graph::hasVertex)
        .def("get_vertex", &Graph::getVertex, py::return_value_policy::reference_internal)
        .def("get_all_vertices", &Graph::getAllVertices)
        .def("get_all_edges", &Graph::getAllEdges)
        .def("get_vertex_count", &Graph::getVertexCount)
        .def("clear", &Graph::clear)
        .def("reset", &Graph::reset) 
        .def_static("load_from_files", &Graph::loadFromFiles)
        .def("__len__", &Graph::getVertexCount)
        .def("__repr__", [](const Graph& g) {
            return "<Graph with " + std::to_string(g.getVertexCount()) + " vertices>";
        });
    
    // Class Graph_Matrix
    py::class_<Graph_Matrix>(m, "Graph_Matrix")
        .def(py::init<>())
        .def("add_edge", &Graph_Matrix::addEdge)
        .def("get_all_edges", &Graph_Matrix::getAllEdges)
        .def("get_vertex_count", &Graph_Matrix::getVertexCount)
        .def("reset", &Graph_Matrix::reset)
        .def_static("load_from_files", &Graph_Matrix::loadFromFiles)
        .def("__len__", &Graph_Matrix::getVertexCount)
        .def("__repr__", [](const Graph_Matrix& g) {
            return "<Graph with " + std::to_string(g.getVertexCount()) + " vertices>";
        });

    m.def("dijkstra_shortest_path", &dijkstra_shortest_path,
          "Find shortest path using A* algorithm",
          py::arg("graph"), py::arg("start"), py::arg("end"));

    m.def("dijkstra_one_to_all", &dijkstra_one_to_all,
          "Find shortest paths from one source to all vertices using A*",
          py::arg("graph"), py::arg("start"));    

    m.def("astar_shortest_path", &astar_shortest_path,
          "Find shortest path using A* algorithm",
          py::arg("graph"), py::arg("start"), py::arg("end"));
    
    m.def("floyd_warshall_all_pairs", &floyd_warshall_all_pairs,
          "Compute all-pairs shortest paths using Floyd-Warshall",
          py::arg("graph_matrix"));
    
    m.def("floyd_warshall_get_path", &floyd_warshall_get_path,
          "Extract path from Floyd-Warshall result",
          py::arg("fw_result"), py::arg("start"), py::arg("end"));

    m.def("mat_mul_all_pairs", &mat_mul_all_pairs,
          "Compute all-pairs shortest paths using Mat-Mul",
          py::arg("graph_matrix"));
    
    m.def("mat_mul_get_path", &matmul_get_path,
          "Extract path from Mat-Mul result",
          py::arg("matmul_result"), py::arg("start"), py::arg("end"));
        
    m.def("kruskal_mst", &kruskal_mst,
          "Find minimum spanning tree using Kruskal's algorithm",
          py::arg("graph"));
    
    m.def("prim_mst", &prim_mst,
          "Find minimum spanning tree using Prim's algorithm",
          py::arg("graph"), py::arg("start_vertex"));

    m.def("version", []() {
        return "Chengdu Metro Core 1.0.0, Gary Agasa 2025";
    });
    
    m.def("test_connection", []() {
        return "C++ extension loaded successfully!";
    });
}