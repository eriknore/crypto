flags = -std=c++11 -Wall
compiler = clang++

all: main

remake: clean main

main: dictionary.o
	$(compiler) $(flags) build/$^ main.cpp -o crypto

dictionary.o: resources/dictionary.cpp 
	$(compiler) $(flags) -c $^ -o build/$@

clean:
	rm -f *.out build/*.o

run: main
	./crypto

valgrind: 
	valgrind --tool=memcheck --leak-check=yes -v ./crypto
