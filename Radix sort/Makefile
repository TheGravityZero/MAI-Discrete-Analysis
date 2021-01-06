CC = g++
OUTPUT = solution
FLAGS = -std=c++14 -O2 -Wextra -Wall -Werror -Wno-sign-compare -pg -Wno-unused-result -pedantic

all: main.cpp vector.hpp
	$(CC) $(FLAGS) main.cpp -o $(OUTPUT)
	
clean:
	rm -rf $(OUTPUT)