"""
Main program for the Chengdu Metro Map, generatring the GUI

Gary Agasa 2025, All rights reserved
"""

from PyQt5.QtWidgets import QWidget, QApplication, QVBoxLayout
from PyQt5.QtWidgets import QSizePolicy
import sys 
import os

# 添加当前目录到 Python 搜索路径
# current_dir = os.path.dirname(os.path.abspath(__file__))
# project_root = os.path.dirname(current_dir)
if getattr(sys, 'frozen', False):
    # 如果是打包后的 exe 运行，资源在临时目录 sys._MEIPASS 中
    project_root = sys._MEIPASS
else:
    # 如果是源码运行
    current_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(current_dir)

if project_root not in sys.path:
    sys.path.insert(0, project_root)

import Ui_navigator
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg
from matplotlib.figure import Figure
import numpy as np 
import matplotlib.image as image

# 使用新的算法接口
from metro_algorithms import (
    createGraph,
    createGraph_Matrix, 
    oneToAllShortestPath, 
    shortedPathBetweenTwoPoints_by_AStar, 
    shortedPathBetweenTwoPoints_by_Dijkstra,
    shortedPathBetweenTwoPoints_by_FW,
    shortedPathBetweenTwoPoints_by_MM,
    kruskal, 
    prim 
)

from data_loader import pointsToCoordinates, findClosestPoints, checkValidPoint, pathsToEdges

# 加载地图图片
try:
    im = image.imread(os.path.join(project_root, 'data', 'cd_metro.png'))
except FileNotFoundError:
    print("cannot find the background map")

vertex_file = os.path.join(project_root, 'data', 'vertex.txt')

class MatplotlibWidget(QWidget):
    def __init__(self, parent=None):
        super(MatplotlibWidget, self).__init__(parent)
        # 设置更大的画布尺寸
        self.figure = Figure(figsize=(10, 8))  
        self.canvas = FigureCanvasQTAgg(self.figure)
        self.axis = self.figure.add_subplot(111)
        self.layoutvertical = QVBoxLayout(self)
        self.layoutvertical.setContentsMargins(0, 0, 0, 0)
        self.layoutvertical.setSpacing(0)
        self.layoutvertical.addWidget(self.canvas)
        self.setMinimumSize(600, 400)
        self.canvas.setMinimumSize(600, 400)
        self.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        self.canvas.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)


class MainWidget(QWidget, Ui_navigator.Ui_Form):
    global im
    
    def __init__(self):
        super(MainWidget, self).__init__()
        self.setupUi(self)
        # 强制放大地图显示区域
        self.widget.setMinimumSize(1000, 750)
        self.widget.setMaximumSize(16777215, 16777215)  # 允许无限大
        self.widget.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        self.init_widget()

        # 连接按钮事件
        self.pushButton.clicked.connect(self.oneToOne)
        self.pushButton_2.clicked.connect(self.oneToAll)
        self.pushButton_3.clicked.connect(self.calculate_mst)
        # self.pushButton_4.clicked.connect(self.busRoute)

        # 初始化界面状态
        self.tab = 1
        self.radioButton.setChecked(True)
        self.radioButton_4.setChecked(True)
        self.radioButton_5.setChecked(True)
        
        self.init_operation_3()
        
        # 创建图实例 - 使用新的C++接口
        print("正在加载地图数据...")
        try:
            self.G = createGraph()
            self.G_m = createGraph_Matrix()
            print("地图数据加载成功，使用C++算法引擎")
        except Exception as e:
            print(f"加载地图数据失败: {e}")
            self.G = None
            self.G_m = None

        self.tabWidget.currentChanged.connect(self.tabChanged)

    def tabChanged(self):
        if self.tabWidget.currentIndex() == 0:
            self.init_operation_1()
        elif self.tabWidget.currentIndex() == 1:
            self.init_operation_2()
        elif self.tabWidget.currentIndex() == 2:
            self.init_operation_3()

    def init_operation_1(self):
        """初始化操作一"""
        self.clearMap()
        self.lineEdit.clear()
        self.lineEdit_2.clear()
        self.textBrowser.clear()
        self.myPrint('Function 1: Shortest Path One to One \n')

    def init_operation_2(self):
        """初始化操作二"""
        self.clearMap()
        self.lineEdit_3.clear()
        self.textBrowser.clear()
        self.myPrint('Function 2: Shortest Path One to All \n')

    def init_operation_3(self):
        """初始化操作三"""
        self.clearMap()
        self.textBrowser.clear()
        self.myPrint('Function 3: Minimum Spanning Tree \n')

    def init_widget(self):
        """初始化绘图组件"""
        # 清空 self.widget 的原有布局和控件
        from PyQt5.QtWidgets import QVBoxLayout, QWidget
        # 移除原有布局
        old_layout = self.widget.layout()
        if old_layout is not None:
            QWidget().setLayout(old_layout)  # 解除原有布局
        # 移除所有子控件
        for child in self.widget.children():
            if isinstance(child, QWidget):
                child.setParent(None)
        # 新建 matplotlib 画布
        self.matplotlibwidget = MatplotlibWidget()
        self.matplotlibwidget.canvas.mpl_connect('button_press_event', self.on_canvas_click)
        layout = QVBoxLayout(self.widget)
        layout.setContentsMargins(0, 0, 0, 0)
        layout.setSpacing(0)
        layout.addWidget(self.matplotlibwidget)
        self.widget.setLayout(layout)
        self.matplotlibwidget.axis.imshow(im)

    def on_canvas_click(self, event):
        """处理画布点击事件"""
        if event.inaxes is not None:
            x, y = event.xdata, event.ydata
            pointName = findClosestPoints(x, y)
            
            if self.tabWidget.currentIndex() == 0:
                start = self.lineEdit.text()
                terminal = self.lineEdit_2.text()
                if len(start) != 0 and len(terminal) != 0:  # reset
                    self.lineEdit.clear()
                    self.lineEdit_2.clear()
                    self.clearMap()

                start = self.lineEdit.text()
                terminal = self.lineEdit_2.text()
                if len(start) == 0:  # if lineEdit has no input
                    self.lineEdit.setText(pointName)
                elif len(terminal) == 0:  # if the lineEdit_2 has no input:
                    self.lineEdit_2.setText(pointName)

            elif self.tabWidget.currentIndex() == 1:
                self.lineEdit_3.setText(pointName)

            elif self.tabWidget.currentIndex() == 3:
                self.clearMap()
                self.lineEdit_4.setText(pointName)

    def clearMap(self):
        """清空地图显示"""
        self.matplotlibwidget.axis.clear()
        self.matplotlibwidget.axis.plot((0), (0), linewidth=0.0001)
        self.matplotlibwidget.axis.imshow(im)
        self.matplotlibwidget.canvas.draw()

    def myPrint(self, mes):
        """在文本浏览器中打印消息"""
        self.textBrowser.insertPlainText(str(mes))

    def myPlot(self, f, t):
        """在地图上绘制路径"""
        xx, yy = pointsToCoordinates(f, t)
        self.matplotlibwidget.axis.plot(xx, yy, 'gold', linewidth=7)
        self.matplotlibwidget.canvas.draw()

# =================================================================================================
# ============================ FUNCTION 1: SHORTEST PATH ONE TO ONE ===============================
# =================================================================================================
    def oneToOne(self):
        """操作一：两点最短路径"""
        if self.G is None:
            self.myPrint('错误：地图数据未正确加载！\n')
            return

        start = self.lineEdit.text()
        terminal = self.lineEdit_2.text()
        valid = checkValidPoint(start) and checkValidPoint(terminal)

        if not valid:
            self.textBrowser.clear()
            self.myPrint('请输入正确的起点与终点！\n\n')
            return

        try:
            if self.radioButton.isChecked():  # MatMul
                path, distance = shortedPathBetweenTwoPoints_by_MM(self.G_m, start, terminal)
            elif self.radioButton_2.isChecked():  # Floyd-Warshall
                path, distance = shortedPathBetweenTwoPoints_by_FW(self.G_m, start, terminal)
            elif self.radioButton_7.isChecked():  # A*
                path, distance = shortedPathBetweenTwoPoints_by_AStar(self.G, start, terminal)
            elif self.radioButton_8.isChecked():  # Dijkstra
                path, distance = shortedPathBetweenTwoPoints_by_Dijkstra(self.G, start, terminal)

            self.matplotlibwidget.axis.clear()
            self.matplotlibwidget.axis.imshow(im)
            self.textBrowser.clear()
            self.myPrint('路线为：\n')
            n = len(path)
            for index, v in enumerate(path):
                if index == n - 1:
                    self.myPrint(v)
                    self.myPrint('\n')
                    break
                f = v
                t = path[index + 1]
                self.myPlot(f, t)
                self.myPrint(v)
                self.myPrint(' --> ')
            self.myPrint('路线长度为：')
            self.myPrint(round(distance, ndigits=1))
        except Exception as e:
            self.textBrowser.clear()
            self.myPrint(f'计算路径时,发生错误：{e}\n')

# =================================================================================================
# ============================ FUNCTION 2: SHORTEST PATH ONE TO ALL ===============================
# =================================================================================================
    def oneToAll(self):
        """操作二：单源全目标最短路径"""
        if self.G is None:
            self.myPrint('错误：地图数据未正确加载！\n')
            return

        start = self.lineEdit_3.text()
        valid = checkValidPoint(start)

        if not valid:
            self.textBrowser.clear()
            self.myPrint('请输入正确的起点！\n')
            return

        try:
            vertices = self.G.get_vertices()
            vertices = list(sorted(vertices))

            if self.radioButton_4.isChecked():      # Mat-Mul
                results = [shortedPathBetweenTwoPoints_by_MM(self.G_m, start, v) for v in vertices if v != start]
            elif self.radioButton_9.isChecked():    # A*
                results = [shortedPathBetweenTwoPoints_by_AStar(self.G, start, v) for v in vertices if v != start]
            elif self.radioButton_3.isChecked():    # Floyd-Warshall
                results = [shortedPathBetweenTwoPoints_by_FW(self.G_m, start, v) for v in vertices if v != start]
            elif self.radioButton_10.isChecked():   # Dijkstra
                # results = [shortedPathBetweenTwoPoints_by_Dijkstra(self.G, start, v) for v in vertices if v != start]
                results = oneToAllShortestPath(self.G, start)
    

            self.textBrowser.clear()
            for item in results:
                path, distance = item
                if len(path) > 0:
                    terminal = path[-1]
                    self.myPrint('\n终点为：\n')
                    self.myPrint(terminal)
                    self.myPrint('\n路线为：\n')
                    n = len(path)
                    for index, v in enumerate(path):
                        if index == n - 1:
                            self.myPrint(v)
                            self.myPrint('\n')
                            break
                        self.myPrint(v)
                        self.myPrint(' --> ')
                    self.myPrint('路线长度为：')
                    self.myPrint(round(distance, ndigits=1))
                    self.myPrint('\n\n')
        except Exception as e:
            self.textBrowser.clear()
            self.myPrint(f'计算路径时,发生错误：{e}\n')

    # =================================================================================================
    # ============================ FUNCTION 3: Minimum Spannning Tree =================================
    # =================================================================================================
    def calculate_mst(self):
        """操作三：最小生成树计算 (Kruskal 或 Prim)"""
        if self.G is None:
            self.myPrint('错误：地图数据未正确加载！\n')
            return
            
        try:
            if self.radioButton_5.isChecked():
                # Kruskal
                MST_edges, distance = kruskal(self.G)
                algo_name = "Kruskal"
            elif self.radioButton_6.isChecked():
                # Prim
                start = 'H' # Default start node for Prim as per original code
                MST_edges, distance = prim(self.G, start)
                algo_name = "Prim"
            else:
                self.myPrint('Choose Kruskal or Prim \n')
                return

            # show and plot
            self.textBrowser.clear()
            self.clearMap()
            self.myPrint('最小生成树的总长度为：\n')
            self.myPrint(round(distance, ndigits=1))
            self.myPrint('\n地铁线路包含以下的边：\n')
            for e in MST_edges:
                u, v = e
                self.myPlot(u, v)
                self.myPrint('(' + u + ',' + v + ')\n')
        except Exception as e:
            self.textBrowser.clear()
            self.myPrint(f'计算最小生成树时发生错误：{e}\n')


if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = MainWidget()
    w.show()
    sys.exit(app.exec_())