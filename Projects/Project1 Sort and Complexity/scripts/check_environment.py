# scripts/check_environment.py
import os
import subprocess
import sys

print("=" * 50)
print("环境诊断信息")
print("=" * 50)

# 1. 检查当前工作目录
print(f"当前工作目录: {os.getcwd()}")

# 2. 检查PATH环境变量
print("\nPATH环境变量:")
for path in os.environ.get('PATH', '').split(';'):
    if 'mingw' in path.lower() or 'gcc' in path.lower():
        print(f"  ✓ {path}")

# 3. 尝试直接运行g++
print("\n尝试直接运行g++:")
try:
    result = subprocess.run(['g++', '--version'], 
                          capture_output=True, text=True, timeout=10)
    print(f"g++ 退出代码: {result.returncode}")
    if result.returncode == 0:
        print("g++ 输出:", result.stdout[:100] + "...")
    else:
        print("g++ 错误:", result.stderr)
except Exception as e:
    print(f"运行g++时出错: {e}")

# 4. 检查where命令找到的g++
print("\n检查where命令:")
try:
    result = subprocess.run(['where', 'g++'], 
                          capture_output=True, text=True, timeout=10)
    print("where g++ 结果:", result.stdout.strip())
except Exception as e:
    print(f"where命令出错: {e}")

# 5. 检查PowerShell中的g++
print("\n检查PowerShell中的Get-Command:")
try:
    result = subprocess.run(['powershell', '-Command', 'Get-Command g++'], 
                          capture_output=True, text=True, timeout=10)
    print("Get-Command结果:", result.stdout)
except Exception as e:
    print(f"Get-Command出错: {e}")