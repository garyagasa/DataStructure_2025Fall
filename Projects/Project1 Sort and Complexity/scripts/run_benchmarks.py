# scripts/run_benchmarks.py
import subprocess
import os
import sys

def build_and_run():
    # 切换到cpp_code目录
    os.chdir('../cpp_code')
    
    # 使用g++直接编译（Windows上可能是g++或cl）
    compile_cmd = [
        'g++', 
        '-std=c++17', 
        '-O2', 
        '-o', 
        'benchmark.exe', 
        'benchmark.cpp'
    ]
    
    try:
        # 尝试使用g++编译
        result = subprocess.run(compile_cmd, check=True, capture_output=True, text=True)
        print("编译成功")
    except (subprocess.CalledProcessError, FileNotFoundError):
        # 如果g++不存在，尝试使用Visual Studio的cl编译器
        try:
            compile_cmd = [
                'cl', 
                '/EHsc', 
                '/O2', 
                '/std:c++17', 
                'benchmark.cpp',
                '/Febenchmark.exe'
            ]
            result = subprocess.run(compile_cmd, check=True, capture_output=True, text=True)
            print("使用cl编译器编译成功")
        except (subprocess.CalledProcessError, FileNotFoundError) as e:
            print(f"编译失败: {e}")
            print("请确保已安装C++编译器（MinGW或Visual Studio）")
            return False
    
    # 运行基准测试
    try:
        subprocess.run(['./benchmark.exe'], check=True)
        print("基准测试运行完成")
        return True
    except subprocess.CalledProcessError as e:
        print(f"基准测试运行失败: {e}")
        return False

if __name__ == "__main__":
    success = build_and_run()
    if success:
        print("现在运行可视化脚本...")
        os.chdir('../scripts')
        subprocess.run([sys.executable, 'visualize_results.py'])
    else:
        print("请检查错误并重试")