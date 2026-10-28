import tkinter as tk
from tkinter import messagebox
import ctypes
import platform
import os
import sys

# --- 1. 加载 C++ 动态链接库 ---

# 获取当前脚本所在的目录
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
# 将SCRIPT_DIR添加到系统路径，以帮助找到库文件
sys.path.append(SCRIPT_DIR)

# 根据操作系统选择正确的库文件名
if platform.system() == "Windows":
    LIB_NAME = os.path.join(SCRIPT_DIR, "calculator.dll")
elif platform.system() == "Darwin":  # macOS
    LIB_NAME = os.path.join(SCRIPT_DIR, "libcalculator.dylib")
elif platform.system() == "Linux":
    LIB_NAME = os.path.join(SCRIPT_DIR, "libcalculator.so")
else:
    LIB_NAME = None

try:
    if LIB_NAME and os.path.exists(LIB_NAME):
        print(f"尝试加载库: {LIB_NAME}")
        # 加载共享库
        c_lib = ctypes.CDLL(LIB_NAME)
        
        # 定义 C++ 函数的签名
        c_lib.calculate_expression.argtypes = [ctypes.c_char_p]
        c_lib.calculate_expression.restype = ctypes.c_int
        
        print(f"成功加载库: {LIB_NAME}")
    else:
        # 如果找不到库文件，尝试直接加载，让系统自己查找
        try:
            print("尝试直接加载calculator.dll...")
            c_lib = ctypes.CDLL("calculator.dll")
            c_lib.calculate_expression.argtypes = [ctypes.c_char_p]
            c_lib.calculate_expression.restype = ctypes.c_int
            print("成功直接加载calculator.dll")
            LIB_NAME = "calculator.dll"
        except Exception as direct_load_error:
            print(f"直接加载失败: {direct_load_error}")
except OSError as e:
    LIB_LOAD_ERROR_MSG = f"无法加载C++库。\n错误: {e}\n\n请确保calculator.dll已正确编译并位于程序目录下。\n当前尝试加载的路径: {LIB_NAME}"
    print(LIB_LOAD_ERROR_MSG)
except Exception as e:
    print(f"调用C++库错误: {e}")
    raise

# --- 2. GUI 实现 ---

class CalculatorApp:
    def __init__(self, master):
        self.master = master
        master.title("CalculatorDIY(2025 WSQ All Rights Reserved)")

        # 当前表达式存储为字符串
        self.expression = tk.StringVar()
        self.expression.set("0")
        self.clear_on_next_digit = False # 标志位：按键后是否应该清空显示

        # 显示区域 (Entry Widget)
        self.display = tk.Entry(master, textvariable=self.expression, font=('Times New Roman', 24), 
                                bd=10, relief=tk.SUNKEN, justify='right', state='readonly')
        self.display.grid(row=0, column=0, columnspan=4, sticky="nsew")

        # 定义按钮布局
        buttons = [
            ('(', 1, 0), (')', 1, 1), ('%', 1, 2), ('C', 1, 3),
            ('7', 2, 0), ('8', 2, 1), ('9', 2, 2), ('/', 2, 3),
            ('4', 3, 0), ('5', 3, 1), ('6', 3, 2), ('*', 3, 3),
            ('1', 4, 0), ('2', 4, 1), ('3', 4, 2), ('-', 4, 3),
            ('0', 5, 0), ('[', 5, 1), (']', 5, 2), ('+', 5, 3),
            ('=', 6, 0, 4) # '=' 跨四列
        ]

        # 创建并放置按钮
        for (text, r, c, *span) in buttons:
            cols = span[0] if span else 1
            button = tk.Button(master, text=text, font=('Arial', 18), 
                                command=lambda t=text: self.button_click(t))
            
            # 设置网格布局
            button.grid(row=r, column=c, columnspan=cols, sticky="nsew", padx=2, pady=2)
            
            # 设置行和列的权重，使得界面可以缩放
            master.grid_rowconfigure(r, weight=1)
        
        for i in range(4):
            master.grid_columnconfigure(i, weight=1)


    def button_click(self, char):
        current_text = self.expression.get()

        # 清零键
        if char == 'C':
            self.expression.set("0")
            self.clear_on_next_digit = False
            return

        # 等号键
        if char == '=':
            self.calculate()
            return

        # 处理数字或运算符输入
        
        # 如果当前显示为"0"，且输入的是数字或括号，则清空"0"
        if current_text == "0" and (char.isdigit() or char in "()[]"):
            current_text = ""
        
        # 如果设置了清空标志，且输入的不是运算符
        if self.clear_on_next_digit and char not in "+-*/%()[]":
            current_text = ""
            self.clear_on_next_digit = False

        self.expression.set(current_text + char)
        

    def calculate(self):
        expression = self.expression.get()
        if not expression:
            self.expression.set("0")
            return

        # 如果表达式只包含数字，直接显示
        if expression.isdigit():
            self.clear_on_next_digit = True
            return

        try:
            # 将 Python 字符串编码为 C 风格的字节串 (UTF-8)
            expression_bytes = expression.encode('utf-8')
            
            # 调用 C++ 库函数
            result_int = c_lib.calculate_expression(expression_bytes)
                       
            # 假设你的 C++ 核心库使用 -99999999 或其他特殊值表示错误
            if result_int == -99999999: 
                self.expression.set("Error!")
                messagebox.showerror("计算错误", "C++ 核心计算函数报告了错误。请检查表达式。")
            else:
                # 显示计算结果
                self.expression.set(str(result_int))
                
            # 计算完成后，下一个数字输入应该清空显示
            self.clear_on_next_digit = True

        except Exception as e:
            # 捕获 Python 或 ctypes 相关的错误
            print(f"计算异常: {e}")
            self.expression.set("Error!")
            messagebox.showerror("Python/CTypes 错误", f"调用 C++ 库时发生错误: {e}")
            self.clear_on_next_digit = True

if __name__ == "__main__":
    root = tk.Tk()
    # 如果有库加载错误，初始化后弹窗提示
    if 'LIB_LOAD_ERROR_MSG' in globals():
        messagebox.showerror("库加载错误", LIB_LOAD_ERROR_MSG)
    app = CalculatorApp(root)
    root.mainloop()