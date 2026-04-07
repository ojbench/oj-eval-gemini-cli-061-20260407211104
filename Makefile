SRCS = $(wildcard *.cpp)

code: $(SRCS) complex.hpp
	g++ $(SRCS) -o code -O2 -std=c++17