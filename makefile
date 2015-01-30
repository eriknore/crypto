flags = -std=c++11 -Wall
compiler = clang++
files = shift_cipher
#build/dictionary.o build/shift.o build/substitution.o

all: $(files)

remake: clean $(files)

shift_cipher: build/dictionary.o build/shift.o
	$(compiler) $(flags) $^ src/$@.cpp -o $@

build/dictionary.o: resources/dictionary.cpp 
	$(compiler) $(flags) -c $^ -o $@

build/shift.o: ciphers/shift.cpp 
	$(compiler) $(flags) -c $^ -o $@

build/substitution.o: ciphers/substitution.cpp 
	$(compiler) $(flags) -c $^ -o $@

tools/ngrams:
	cd tools/ngrams && make
	mv tools/ngrams/ngrams .

clean:
	rm -f *.out build/*.o

valgrind: 
	valgrind --tool=memcheck --leak-check=yes -v ./crypto
