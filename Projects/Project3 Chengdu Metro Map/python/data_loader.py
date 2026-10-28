"""
数据加载模块 - 处理地图数据的加载和坐标转换
"""

from typing import Tuple, Dict, List
import os
import sys  # 新增导入

class DataLoader:
    """数据加载器"""
    
    def __init__(self, base_path: str = None):
        if base_path is None:
            if getattr(sys, 'frozen', False):
                self.base_path = os.path.join(sys._MEIPASS, 'data')
            else:
                current_dir = os.path.dirname(os.path.abspath(__file__))
                self.base_path = os.path.join(current_dir, '..', 'data')
        else:
            self.base_path = base_path

        self.vertex_coords: Dict[str, Tuple[float, float]] = {}
        self.point_names: str = ""
        self._load_vertex_data()
    
    def _load_vertex_data(self):
        """加载顶点坐标数据"""
        vertex_file = os.path.join(self.base_path, 'vertex.txt')
            
        print(f"Loading vertex file from: {vertex_file}")  # 调试信息
        with open(vertex_file, 'r') as f:
            vertex_list = []
            for line in f:
                x, y = eval(line.strip())
                vertex_list.append((x, y))
        
        # 生成顶点名称（与原utils.py保持一致）
        num_vertices = len(vertex_list)
        if num_vertices <= 52:
            uppercase = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
            lowercase = 'abcdefghijklmnopqrstuvwxyz'
            self.point_names = uppercase + lowercase[:num_vertices-26]
        else:
            raise ValueError(f"不支持超过52个节点，当前节点数: {num_vertices}")
        
        # 建立顶点名称到坐标的映射
        self.vertex_coords = dict(zip(self.point_names, vertex_list))
    
    def get_edge_file_path(self) -> str:
        """获取边文件路径"""
        return os.path.join(self.base_path, "edge.txt")
    
    def get_vertex_file_path(self) -> str:
        """获取顶点文件路径"""
        return os.path.join(self.base_path, "vertex.txt")
    
    def get_vertex_coords(self, vertex_id: str) -> Tuple[float, float]:
        """获取顶点坐标"""
        return self.vertex_coords.get(vertex_id, (0, 0))
    
    def get_all_vertices(self) -> List[str]:
        """获取所有顶点名称"""
        return list(self.point_names)
    
    def check_valid_point(self, vertex_name: str) -> bool:
        """检查顶点名称是否有效"""
        return vertex_name in self.point_names
    
    def find_closest_point(self, x: float, y: float) -> str:
        """根据坐标找到最近的顶点"""
        min_dist = float('inf')
        closest_point = None
        
        for point_name in self.point_names:
            pos_x, pos_y = self.vertex_coords[point_name]
            dist = (pos_x - x) ** 2 + (pos_y - y) ** 2
            if dist < min_dist:
                min_dist = dist
                closest_point = point_name
        
        return closest_point
    
    def points_to_coordinates(self, u: str, v: str) -> Tuple[Tuple[float, float], Tuple[float, float]]:
        """
        给定两个标记点的名称u和v，返回u和v的x坐标，以及u和v的y坐标；
        即返回：(u_x,v_x), (u_y,v_y)；
        用于辅助matplotlib绘图
        """
        u_coord = self.vertex_coords[u]
        v_coord = self.vertex_coords[v]
        xx = (u_coord[0], v_coord[0])
        yy = (u_coord[1], v_coord[1])
        return xx, yy

# 全局数据加载器实例
_data_loader = None

def get_data_loader() -> DataLoader:
    """获取全局数据加载器实例"""
    global _data_loader
    if _data_loader is None:
        _data_loader = DataLoader()
    return _data_loader

# 兼容性函数
def pointsToCoordinates(u: str, v: str):
    """兼容原接口的坐标转换函数"""
    return get_data_loader().points_to_coordinates(u, v)

def findClosestPoints(x: float, y: float) -> str:
    """兼容原接口的最近点查找函数"""
    return get_data_loader().find_closest_point(x, y)

def checkValidPoint(vertex_name: str) -> bool:
    """兼容原接口的点有效性检查函数"""
    return get_data_loader().check_valid_point(vertex_name)

def pathsToEdges(loc_path_dist, G_edges):
    """
    给定一些路径，返回去重后的边，以及总的长度，用于操作四，转化Dijkstra的返回结果
    兼容原接口
    """
    total_dist = 0
    edges = []
    for item in loc_path_dist:
        _, path, dist = item
        for index, u in enumerate(path):
            if index == len(path) - 1:
                break
            v = path[index + 1]
            if (u, v) in edges or (v, u) in edges:
                continue
            edges.append((u, v))
            # 计算实际边权重
            if hasattr(G_edges, '__getitem__'):
                if (u, v) in G_edges:
                    total_dist += G_edges[(u, v)]
                elif (v, u) in G_edges:
                    total_dist += G_edges[(v, u)]
            else:
                # 如果G_edges有不同的接口
                total_dist += dist
    
    return edges, total_dist