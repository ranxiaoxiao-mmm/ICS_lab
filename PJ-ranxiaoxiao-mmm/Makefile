CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

TARGET = cpu

all: $(TARGET)

cpu:
	$(CXX) $(CXXFLAGS) -o cpu CPU.cpp 

clean:
	rm -f $(TARGET) 

.PHONY: all clean
