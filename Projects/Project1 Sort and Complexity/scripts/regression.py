import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import seaborn as sns

# 设置中文字体和图形样式
plt.rcParams['font.sans-serif'] = ['SimHei', 'Arial']
plt.rcParams['axes.unicode_minus'] = False
sns.set_style("whitegrid")

def n_squared(x, a):
    """n^2 回归函数"""
    return a * x**2

def n_log_n(x, a):
    """n*log(n) 回归函数"""
    return a * x * np.log(x)

def analyze_sorting_data(csv_data):
    """
    分析排序算法数据并进行回归分析
    """
    # 创建DataFrame
    df = csv_data
    
    # 分离数据
    insertion_data = df[df['algorithm'] == 'Insertion_sort']
    quick_data = df[df['algorithm'] == 'Quick_sort']
    
    # 提取参数
    n_insertion = insertion_data['parameter'].values
    time_insertion = insertion_data['time_us'].values
    
    n_quick = quick_data['parameter'].values
    time_quick = quick_data['time_us'].values
    
    # 回归分析
    # Insertion Sort - n^2 回归
    popt_insertion, pcov_insertion = curve_fit(n_squared, n_insertion, time_insertion)
    a_insertion = popt_insertion[0]
    
    # Quick Sort - n*log(n) 回归
    popt_quick, pcov_quick = curve_fit(n_log_n, n_quick, time_quick)
    a_quick = popt_quick[0]
    
    # 生成拟合曲线数据点
    n_fit = np.linspace(min(n_insertion.min(), n_quick.min()), 
                       max(n_insertion.max(), n_quick.max()), 1000)
    
    fit_insertion = n_squared(n_fit, a_insertion)
    fit_quick = n_log_n(n_fit, a_quick)
    
    # 创建可视化图形
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))
    
    # 第一个子图：原始数据对比
    ax1.scatter(n_insertion, time_insertion, alpha=0.7, label='Insertion Sort 实际数据', color='red')
    ax1.scatter(n_quick, time_quick, alpha=0.7, label='Quick Sort 实际数据', color='blue')
    ax1.plot(n_fit, fit_insertion, 'r--', label=f'Insertion Sort拟合: {a_insertion:.2e} * n²', linewidth=2)
    ax1.plot(n_fit, fit_quick, 'b--', label=f'Quick Sort拟合: {a_quick:.2e} * n*log(n)', linewidth=2)
    
    ax1.set_xlabel('数据规模 (n)')
    ax1.set_ylabel('时间 (微秒)')
    ax1.set_title('排序算法性能比较')
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    
    # 第二个子图：对数尺度对比
    ax2.scatter(n_insertion, time_insertion, alpha=0.7, label='Insertion Sort', color='red')
    ax2.scatter(n_quick, time_quick, alpha=0.7, label='Quick Sort', color='blue')
    ax2.plot(n_fit, fit_insertion, 'r--', linewidth=2)
    ax2.plot(n_fit, fit_quick, 'b--', linewidth=2)
    
    ax2.set_xlabel('数据规模 (n)')
    ax2.set_ylabel('时间 (微秒)')
    ax2.set_title('排序算法性能比较 (对数尺度)')
    ax2.set_yscale('log')
    ax2.set_xscale('log')
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.show()
    
    # 打印回归结果
    print("=" * 60)
    print("回归分析结果")
    print("=" * 60)
    print(f"Insertion Sort (O(n²)) 回归常数: {a_insertion:.6e}")
    print(f"Quick Sort (O(n log n)) 回归常数: {a_quick:.6e}")
    print()
    
    # 计算R²值来评估拟合质量
    def r_squared(y_actual, y_predicted):
        ss_res = np.sum((y_actual - y_predicted) ** 2)
        ss_tot = np.sum((y_actual - np.mean(y_actual)) ** 2)
        return 1 - (ss_res / ss_tot)
    
    r2_insertion = r_squared(time_insertion, n_squared(n_insertion, a_insertion))
    r2_quick = r_squared(time_quick, n_log_n(n_quick, a_quick))
    
    print("拟合质量评估 (R²值):")
    print(f"Insertion Sort R²: {r2_insertion:.6f}")
    print(f"Quick Sort R²: {r2_quick:.6f}")
    print()
    
    # 预测更大规模数据的性能
    print("性能预测 (更大规模):")
    n_predict = [100000, 500000, 1000000]
    for n in n_predict:
        t_insertion = n_squared(n, a_insertion)
        t_quick = n_log_n(n, a_quick)
        ratio = t_insertion / t_quick if t_quick > 0 else float('inf')
        print(f"n = {n:,}: Insertion ≈ {t_insertion:,.0f} μs, Quick ≈ {t_quick:,.0f} μs, 比率: {ratio:.1f}x")
    
    return {
        'insertion_constant': a_insertion,
        'quick_constant': a_quick,
        'r2_insertion': r2_insertion,
        'r2_quick': r2_quick
    }

# 使用示例
if __name__ == "__main__":
    # 这里直接使用您提供的数据
    csv_data = pd.read_csv('../data/results.csv')
    results = analyze_sorting_data(csv_data)