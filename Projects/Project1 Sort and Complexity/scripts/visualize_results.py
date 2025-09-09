# scripts/visualize_results.py
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import os

def load_and_visualize():
    # 确保数据目录存在
    os.makedirs('../data', exist_ok=True)
    
    # 加载数据
    try:
        df = pd.read_csv('../data/results.csv')
    except FileNotFoundError:
        print("结果文件未找到，请先运行C++基准测试程序")
        return
    
    # 设置绘图风格
    sns.set_style("whitegrid")
    plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
    plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号
    
    # 为每个算法创建子图
    algorithms = df['algorithm'].unique()
    fig, axes = plt.subplots(1, len(algorithms), figsize=(15, 5))
    
    if len(algorithms) == 1:
        axes = [axes]
    
    for i, algorithm in enumerate(algorithms):
        algo_data = df[df['algorithm'] == algorithm]
        
        # 绘制散点图
        axes[i].scatter(algo_data['parameter'], algo_data['time_us'], 
                       alpha=0.6, s=20, label='数据点')
        
        # 计算移动平均以平滑曲线
        window_size = max(1, len(algo_data) // 20)
        moving_avg = algo_data['time_us'].rolling(window=window_size).mean()
        
        # 绘制平滑曲线
        axes[i].plot(algo_data['parameter'], moving_avg, 
                    color='red', linewidth=2, label='移动平均')
        
        axes[i].set_xlabel('参数值（输入大小）')
        axes[i].set_ylabel('执行时间（微秒）')
        axes[i].set_title(f'{algorithm} 执行时间')
        axes[i].legend()
        axes[i].grid(True, linestyle='--', alpha=0.7)
    
    plt.tight_layout()
    plt.savefig('../data/execution_time_plot.png', dpi=300, bbox_inches='tight')
    plt.show()

    
    # 创建第二个图：使用子图展示每个算法的箱线图
    fig, axes = plt.subplots(1, len(algorithms), figsize=(15, 5))
    
    if len(algorithms) == 1:
        axes = [axes]
    
    for i, algorithm in enumerate(algorithms):
        algo_data = df[df['algorithm'] == algorithm]
        
        # 将参数值分组以便箱线图显示
        param_bins = pd.cut(algo_data['parameter'], bins=10)
        boxplot_data = []
        boxplot_labels = []
        
        for bin in param_bins.unique():
            bin_data = algo_data[param_bins == bin]['time_us']
            if len(bin_data) > 0:
                boxplot_data.append(bin_data)
                boxplot_labels.append(f"{bin.left}-{bin.right}")
        
        axes[i].boxplot(boxplot_data, labels=boxplot_labels)
        axes[i].set_xlabel('参数范围')
        axes[i].set_ylabel('执行时间（微秒）')
        axes[i].set_title(f'{algorithm} 执行时间分布')
        plt.setp(axes[i].xaxis.get_majorticklabels(), rotation=45)
    
    plt.tight_layout()
    plt.savefig('../data/execution_time_boxplot.png', dpi=300, bbox_inches='tight')
    plt.show()

if __name__ == "__main__":
    load_and_visualize()