"""
Swapping C++ Algorithms in Python APIs
"""

import metro_core  # C++编译的扩展模块
from typing import List, Tuple, Dict, Optional
from dataclasses import dataclass
import os
import sys

@dataclass
class PathResult:
    """路径查询结果"""
    path: List[str]
    distance: float
    found: bool

@dataclass
class MSTResult:
    """最小生成树结果"""
    edges: List[Tuple[str, str]]
    total_weight: float
    success: bool

class MetroGraph:
    """Graph using adjacent lists to represent"""
    
    def __init__(self):
        self._graph = metro_core.Graph()
    
    def add_vertex(self, vertex_id: str, x: float = 0, y: float = 0):
        """添加顶点"""
        self._graph.add_vertex(vertex_id, x, y)
    
    def add_edge(self, from_vertex: str, to_vertex: str, weight: float):
        """添加边"""
        self._graph.add_edge(from_vertex, to_vertex, weight)
    
    def load_from_files(self, edge_file: str, vertex_file: str):
        """从文件加载图数据"""
        self._graph = metro_core.Graph.load_from_files(edge_file, vertex_file)
    
    def get_vertices(self) -> List[str]:
        """获取所有顶点"""
        return self._graph.get_all_vertices()
    
    def get_vertex_coords(self, vertex_id: str) -> Tuple[float, float]:
        """获取顶点坐标"""
        vertex = self._graph.get_vertex(vertex_id)
        return (vertex.x, vertex.y)
    
    def reset(self):
        self._graph.reset()

class MetroGraph_Matrix:
    """Graph using adjacent matrix to represent"""

    def __init__(self):
        self._graph = metro_core.Graph_Matrix()
    
    def add_edge(self, from_vertex: str, to_vertex: str, weight: float):
        self._graph.add_edge(from_vertex, to_vertex, weight)

    def load_from_files(self, edge_file: str):
        self._graph = metro_core.Graph_Matrix.load_from_files(edge_file)

    def reset(self):
        self._graph.reset()    

class DijkstraAlgorithm:
    """Dijkstra算法接口"""
    
    @staticmethod
    def shortest_path(graph: MetroGraph, start: str, end: str) -> PathResult:
        """单源单目标最短路径"""
        result = metro_core.dijkstra_shortest_path(graph._graph, start, end)
        return PathResult(
            path=result.path,
            distance=result.distance,
            found=result.found
        )
    
    @staticmethod
    def one_to_all_shortest_paths(graph: MetroGraph, start: str) -> Dict[str, PathResult]:
        """单源全目标最短路径"""
        result = metro_core.dijkstra_one_to_all(graph._graph, start)
        return {
            vertex: PathResult(
                path=path_result.path,
                distance=path_result.distance,
                found=path_result.found
            )
            for vertex, path_result in result.results.items()
        }
    
class AstarAlgorithm:
    """Astar算法接口"""
    @staticmethod
    def shortest_path(graph: MetroGraph, start: str, end: str) -> PathResult:
        """单源单目标最短路径"""
        result = metro_core.astar_shortest_path(graph._graph, start, end)
        return PathResult(
            path=result.path,
            distance=result.distance,
            found=result.found
        )

class FloydWarshallAlgorithm:
    """Floyd-Warshall算法接口"""
    
    def __init__(self, graph: MetroGraph_Matrix):
        self._fw_result = metro_core.floyd_warshall_all_pairs(graph._graph)
    
    def shortest_path(self, start: str, end: str) -> PathResult:
        """获取两点间最短路径"""
        result = metro_core.floyd_warshall_get_path(self._fw_result, start, end)
        return PathResult(
            path=result.path,
            distance=result.distance,
            found=result.found
        )

class MatmulAlgorithm:
    """Matmul算法接口"""
    
    def __init__(self, graph: MetroGraph_Matrix):
        self._matmul_result = metro_core.mat_mul_all_pairs(graph._graph)
    
    def shortest_path(self, start: str, end: str) -> PathResult:
        """获取两点间最短路径"""
        result = metro_core.mat_mul_get_path(self._matmul_result, start, end)
        return PathResult(
            path=result.path,
            distance=result.distance,
            found=result.found
        )


class KruskalAlgorithm:
    """Kruskal算法接口"""
    
    @staticmethod
    def minimum_spanning_tree(graph: MetroGraph) -> MSTResult:
        """最小生成树（Kruskal算法）"""
        result = metro_core.kruskal_mst(graph._graph)
        return MSTResult(
            edges=result.edges,
            total_weight=result.total_weight,
            success=result.success
        )

class PrimAlgorithm:
    """Prim算法接口"""
    
    @staticmethod
    def minimum_spanning_tree(graph: MetroGraph, start_vertex: str) -> MSTResult:
        """最小生成树（Prim算法）"""
        result = metro_core.prim_mst(graph._graph, start_vertex)
        return MSTResult(
            edges=result.edges,
            total_weight=result.total_weight,
            success=result.success
        )

# 兼容性函数 - 保持与原有代码的接口一致性
def createGraph() -> MetroGraph:
    """创建并加载地铁图（兼容原接口）"""
    if getattr(sys, 'frozen', False):
        project_root = sys._MEIPASS
    else:
        project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    
    edge_file = os.path.join(project_root, "data", "edge.txt")
    vertex_file = os.path.join(project_root, "data", "vertex.txt")
    
    graph = MetroGraph()
    graph.load_from_files(edge_file, vertex_file)
    return graph

def createGraph_Matrix() -> MetroGraph_Matrix:
    """创建并加载地铁图(邻接矩阵)（兼容原接口）"""
    if getattr(sys, 'frozen', False):
        project_root = sys._MEIPASS
    else:
        project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        
    edge_file = os.path.join(project_root, "data", "edge.txt")
    
    graph_m = MetroGraph_Matrix()
    graph_m.load_from_files(edge_file)
    return graph_m

def shortedPathBetweenTwoPoints_by_Dijkstra(graph: MetroGraph, from_name: str, to_name: str):
    """Dijkstra两点最短路径（兼容原接口）"""
    graph.reset()
    result = DijkstraAlgorithm.shortest_path(graph, from_name, to_name)
    return result.path, result.distance

def shortedPathBetweenTwoPoints_by_AStar(graph: MetroGraph, from_name: str, to_name: str):
    """A*两点最短路径（兼容原接口）"""
    # Placeholder for A* algorithm implementation
    # Replace with actual logic to compute shortest path using A*
    graph.reset()
    result = AstarAlgorithm.shortest_path(graph, from_name, to_name)
    return result.path, result.distance

def shortedPathBetweenTwoPoints_by_FW(graph: MetroGraph_Matrix, from_name: str, to_name: str):
    """Floyd-Warshall两点最短路径（兼容原接口）"""
    fw = FloydWarshallAlgorithm(graph)
    result = fw.shortest_path(from_name, to_name)
    return result.path, result.distance

def shortedPathBetweenTwoPoints_by_MM(graph: MetroGraph_Matrix, from_name: str, to_name: str):
    """Mat-Mul两点最短路径（兼容原接口）"""
    mm = MatmulAlgorithm(graph)
    result = mm.shortest_path(from_name, to_name)
    return result.path, result.distance

def oneToAllShortestPath(graph: MetroGraph, start_name: str):
    """单源全目标最短路径（兼容原接口）, 使用Dijkstra算法"""
    results = DijkstraAlgorithm.one_to_all_shortest_paths(graph, start_name)
    # 转换为原格式：[(terminal, path, distance), ...]
    return [
        (result.path, result.distance)
        for terminal, result in results.items()
        if result.found
    ]

def kruskal(graph: MetroGraph):
    """Kruskal最小生成树（兼容原接口）"""
    result = KruskalAlgorithm.minimum_spanning_tree(graph)
    return result.edges, result.total_weight

def prim(graph: MetroGraph, start_name: str):
    """Prim最小生成树（兼容原接口）"""
    result = PrimAlgorithm.minimum_spanning_tree(graph, start_name)
    return result.edges, result.total_weight