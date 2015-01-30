flags = -std=c++11 -Wall
compiler = clang++
files = crack_shift tools/ngrams
c_sub = crack_subst
b = ../build

all: $(files)

remake: clean $(files)

crack_shift: $(b)/dictionary.o $(b)/shift.o ../src/shift_cipher_crack.cpp
	$(compiler) $(flags) $^ -o $@

$(b)/dictionary.o: ../tools/dictionary/dictionary.cpp 
	$(compiler) $(flags) -c $^ -o $@

$(b)/shift.o: ../ciphers/shift.cpp 
	$(compiler) $(flags) -c $^ -o $@

tools/ngrams: FORCE
	cd ../tools/ngrams && make
	cp ../tools/ngrams/ngrams $(c_sub)/ngrams

FORCE:

clean:
	rm -f crack_shift $(c_sub)/ngrams $(c_sub)/ic_calc $(c_sub)/subst_cipher

rm_files:
	rm -f cipher key decrypted

valgrind: 
	valgrind --tool=memcheck --leak-check=yes -v ./crypto
