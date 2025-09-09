# scripts/run_benchmarks.py
import subprocess
import os
import sys

def build_and_run():
    print("切换到cpp_code目录...")
    original_dir = os.getcwd()
    os.chdir('../cpp_code')
    
    # 使用诊断中找到的完整路径
    gpp_path = r"C:\w64devkit\bin\g++.exe"
    
    print(f"使用编译器: {gpp_path}")
    
    try:
        # 编译命令
        compile_cmd = [
            gpp_path,
            '-std=c++17', 
            '-O2', 
            '-o', 
            'benchmark.exe', 
            'benchmark.cpp'
        ]
        
        print(f"运行命令: {' '.join(compile_cmd)}")
        
        # 编译
        result = subprocess.run(compile_cmd, 
                              check=True, 
                              capture_output=True, 
                              text=True,
                              timeout=60)
        
        print("✓ 编译成功")
        if result.stderr:
            print("编译警告:", result.stderr)
        
        # 运行基准测试
        print("运行基准测试程序...")
        run_result = subprocess.run(['./benchmark.exe'], 
                                  check=True, 
                                  capture_output=True, 
                                  text=True,
                                  timeout=120)
        
        print("程序输出:")
        print(run_result.stdout)
        
        if run_result.stderr:
            print("程序错误输出:")
            print(run_result.stderr)
            
        print("✓ 基准测试运行完成")
        return True
        
    except subprocess.CalledProcessError as e:
        print(f"进程执行错误: {e}")
        print("标准输出:", e.stdout)
        print("错误输出:", e.stderr)
        return False
    except FileNotFoundError as e:
        print(f"文件未找到错误: {e}")
        return False
    except Exception as e:
        print(f"其他错误: {e}")
        return False
    finally:
        os.chdir(original_dir)

if __name__ == "__main__":
    print("=" * 50)
    print("C++代码执行时间可视化工具")
    print("=" * 50)
    
    success = build_and_run()
    if success:
        print("\n" + "=" * 50)
        print("现在运行可视化脚本...")
        print("=" * 50)
        subprocess.run([sys.executable, 'visualize_results.py'])
    else:
        print("\n运行失败，请检查错误信息")
        input("按Enter键退出...")