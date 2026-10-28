CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

# Windows特定标志
WINDOWS_FLAGS = -shared -static-libgcc -static-libstdc++

# 源文件
SRCS = calculator_core.cpp in2post.h postfix_cal.h string2vec.h
TARGET = calculator.dll
TEST_TG = caltest.exe in2post_test.exe postfix_cal_test.exe

# 默认目标
all: $(TARGET) $(TEST_TG)

# Windows下的DLL构建
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(WINDOWS_FLAGS) -o $(TARGET) $(SRCS)

# 测试程序
caltest.exe: caltest.cpp calculator.h postfix_cal.h in2post.h string2vec.h
	$(CXX) $(CXXFLAGS) -o caltest.exe caltest.cpp

in2post_test.exe: in2post_test.cpp in2post.h string2vec.h
	$(CXX) $(CXXFLAGS) -o in2post_test.exe in2post_test.cpp

postfix_cal_test.exe: postfix_cal_test.cpp postfix_cal.h string2vec.h
	$(CXX) $(CXXFLAGS) -o postfix_cal_test.exe postfix_cal_test.cpp

# 清理
clean:
	rm -f $(TARGET) $(TEST_TG)

.PHONY: all clean test