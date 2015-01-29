flags = -std=c++11 -Wall
compiler = clang++
files = build/dictionary.o build/shift.o build/substitution.o

all: main

remake: clean main

main: $(files)
	$(compiler) $(flags) $^ main.cpp -o crypto

build/dictionary.o: resources/dictionary.cpp 
	$(compiler) $(flags) -c $^ -o $@

build/shift.o: ciphers/shift.cpp 
	$(compiler) $(flags) -c $^ -o $@

build/substitution.o: ciphers/substitution.cpp 
	$(compiler) $(flags) -c $^ -o $@

clean:
	rm -f *.out build/*.o

run: main
	./crypto

valgrind: 
	valgrind --tool=memcheck --leak-check=yes -v ./crypto
