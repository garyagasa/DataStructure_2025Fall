# Makefile for creating the dictionary shared library (DLL)

# Compiler
CXX = g++.exe

# Compiler flags
# -I. includes the current directory for headers (e.g., io.h)
# -shared creates a shared library
# -o specifies the output file name
# -fPIC generates Position-Independent Code, necessary for shared libraries
CXXFLAGS = -I. -shared -o

# Target DLL name
TARGET = dictionary_lib.dll

# Source files
# We only need to compile the library bridge. The compiler will find the included headers.
SOURCES = dictionary_lib.cpp

# Default rule
all: $(TARGET)

# Rule to build the target DLL
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(TARGET) $(SOURCES)

# Clean rule to remove the compiled DLL
clean:
	rm -f $(TARGET)

.PHONY: all clean
