flags = -std=c++11 -Wall
compiler = clang++
files = shift_cipher subst_cipher caesar_cipher
b = build

all: $(files) cryptanalysis

remake: clean $(files)

shift_cipher: $(b)/dictionary.o $(b)/shift.o src/shift_cipher.cpp
	$(compiler) $(flags) $^ -o $@

subst_cipher: $(b)/substitution.o src/subst_cipher.cpp
	$(compiler) $(flags) $^ -o $@

caesar_cipher: $(b)/dictionary.o $(b)/shift.o src/caesar.cpp
	$(compiler) $(flags) $^ -o $@

$(b)/dictionary.o: tools/dictionary/dictionary.cpp 
	$(compiler) $(flags) -c $^ -o $@

$(b)/shift.o: ciphers/shift.cpp 
	$(compiler) $(flags) -c $^ -o $@

$(b)/substitution.o: ciphers/substitution.cpp 
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
