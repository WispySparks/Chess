srcs = $(wildcard src/*.cpp) 

all:
	g++ $(srcs) -o main