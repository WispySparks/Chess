srcs = $(wildcard src/*.cpp) 

all:
	g++ -Wall $(srcs) -o main -std=c++23