flags = -std=c++11 -Wall
compiler = clang++
files = shift_cipher
#build/dictionary.o build/shift.o build/substitution.o

all: $(files)

remake: clean $(files)

shift_cipher: build/dictionary.o build/shift.o src/shift_cipher.cpp
	$(compiler) $(flags) $^ -o $@

build/dictionary.o: tools/dictionary/dictionary.cpp 
	$(compiler) $(flags) -c $^ -o $@

build/shift.o: ciphers/shift.cpp 
	$(compiler) $(flags) -c $^ -o $@

build/substitution.o: ciphers/substitution.cpp 
	$(compiler) $(flags) -c $^ -o $@

tools/ngrams: FORCE
	cd tools/ngrams && make
	mv tools/ngrams/ngrams cryptanalysis/subst/ngrams

FORCE:

clean:
	rm -f shift_cipher subst_cipher cryptanalysis/subst/ngrams cryptanalysis/subst/ic_calc cryptanalysis/subst/subst_cipher
	rm -f build/*.o

valgrind: 
	valgrind --tool=memcheck --leak-check=yes -v ./crypto
