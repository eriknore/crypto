flags = -std=c++11 -Wall
compiler = clang++
files = shift_cipher tools/ngrams

all: $(files) cryptanalysis

remake: clean $(files)

shift_cipher: build/dictionary.o build/shift.o src/shift_cipher.cpp
	$(compiler) $(flags) $^ -o $@

build/dictionary.o: tools/dictionary/dictionary.cpp 
	$(compiler) $(flags) -c $^ -o $@

build/shift.o: ciphers/shift.cpp 
	$(compiler) $(flags) -c $^ -o $@

build/substitution.o: ciphers/substitution.cpp 
	$(compiler) $(flags) -c $^ -o $@

cryptanalysis: FORCE
	cd cryptanalysis && make

FORCE:

clean:
	rm -f shift_cipher subst_cipher
	cd cryptanalysis && make clean
	rm -f build/*.o

rm_files:
	rm -f cipher key decrypted

valgrind: 
	valgrind --tool=memcheck --leak-check=yes -v ./crypto
