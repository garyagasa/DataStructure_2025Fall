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
#### III.