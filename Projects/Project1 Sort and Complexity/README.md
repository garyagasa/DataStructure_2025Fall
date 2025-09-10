### Data Structure Project I: Sort and Complexity
Shiqiang Wu 24300810019@m.fudan.edu.cn
#### I. Project Structure
+ cpp_code: contains all C++ implementation of sort algorithms
   + benchmark.cpp
    code to generate random data to sort and output the result(operating time) to `result.csv`
   + **my_algorithm.h**
    implementation of `insertion sort`, `merge sort`, `quick sort`, `improved sort`
     
    including ***q1***, ***q2***, ***q3***, ***q5***
   + sort_test.cpp
    some test samples to justify the correctness of different sort algorithms
+ scripts: python scripts to run the sort algorithms and visualize the results
   + run_benchmarks.py
    script used to run the `benchmark.cpp`
   + visualize_results.py
    generate the visualization of the operation time
   + check_environment.py 
    check the environment
+ data: `csv` file to record the result and some graphs
   + results.csv  
   + execution_time_boxplot.png
   + execution_time_plot.png
   + execution_time_regression.png

#### II. Dependence Packages and Operation Workflow
1. dependence packages:
   `pandas`, `matplotlib`, `seaborn`, `numpy`
2. operation workflow:
   + step0: check environment
   ```bash
      cd scripts
      python check_environment.py
   ```
   + step1: test sort algorithms correctness
   ```bash
      cd ../cpp_code
      g++ sort_test.cpp -o sort_test
      ./sort_test
   ``` 
   which should show this:
   ```bash
   Merge_sort Int: 0 1 2 2 3 4 5 5 7 8 9 
   Quick_sort Int: 0 1 2 2 3 4 5 5 7 8 9 
   Merge_sort Float: 0.4 1.2 1.7 2 2.5 3 3.1 3.3 6.5 8.2 9.1 
   Quick_sort Float: 0.4 1.2 1.7 2 2.5 3 3.1 3.3 6.5 8.2 9.1 
   Merge_sort Char: $ A F J K T U _ a b f s 
   Quick_sort Char: $ A F J K T U _ a b f s 
   ```
   + step2: run the test and visualize the operation time
   ```bash
      cd ../scripts
      python run_benchmarks.py
   ```
#### III. Operation Time of Different Algorithms and Reflection
![execution time plot1](data/execution_time_plot1.png)
figure1: execution time plot(10-500)

![time boxplot1](data/execution_time_boxplot1.png)
figure2: time bloxplot(10-500)

![time regression1](data/execution_time_regression1.png)
figure3: time regression plot and comparison of different algorithm(10-500)

![execution time plot2](data/execution_time_plot2.png)
figure4: execution time plot(1000-50000)

![time boxplot2](data/execution_time_boxplot2.png)
figure5: time bloxplot(1000-50000)

![time regression2](data/execution_time_regression2.png)
figure6: time regression plot and comparison of different algorithm(1000-50000)

1. Compare the performance of Quick sort and Insertion sort(with tiny scale data)
   In figure 1-3, we compare algorithms with tiny scale data(size range from 10 to 500, step=1), for each size we repeat the experiment with 10 times and get the average result to reduce the randomness error.Notice that in figure3, we use the linear regression to fit the curves of different algorithms.

   Here is the linear fit functions:

   Insertion sort:
   $$y= 0.031649x - 2.31$$
   Quick sort:
   $$y= 0.028215x - 1.11$$

   We then can compute the point where Quick sort outperforms Insertion sort:
   $$x=349.45$$