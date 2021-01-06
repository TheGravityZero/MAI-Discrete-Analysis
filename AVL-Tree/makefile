CC = g++
OUTPUT = solution
FLAGS = -std=c++14 -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic

all: main.cpp bst.hpp bst.cpp
	$(CC) $(FLAGS) -g main.cpp bst.cpp -o $(OUTPUT)
clean:
	rm -rf $(OUTPUT)