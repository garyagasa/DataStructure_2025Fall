# 设置编译器和编译选项
CXX = g++
CXXFLAGS = -std=c++23 -Wall

# 定义目标文件
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

# 定义最终生成的可执行文件
EXEC = benchmark sort_test

# 默认目标
all: $(EXEC)

# 生成 benchmark 可执行文件
benchmark: benchmark.o 
	$(CXX) $(CXXFLAGS) -o benchmark benchmark.o 

# 生成 sort_test 可执行文件
sort_test: sort_test.o 
	$(CXX) $(CXXFLAGS) -o sort_test sort_test.o 

# 生成 .o 文件的规则
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理编译生成的文件
clean:
	rm -f *.o $(EXEC)
