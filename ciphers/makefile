flags = -std=c++11 -Wall
compiler = clang++
files = subst_cipher affine_cipher shift_cipher caesar_cipher vigenere_cipher
bin = ../bin
src = ../src

all: $(files)

remake: clean $(files)

subst_cipher: $(bin)/substitution.o $(src)/subst_cipher.cpp
	$(compiler) $(flags) $^ -o $@

affine_cipher: $(bin)/substitution.o $(bin)/affine.o \
		$(src)/affine_cipher.cpp
	$(compiler) $(flags) $^ -o $@

shift_cipher: $(bin)/substitution.o $(bin)/affine.o $(bin)/shift.o \
		$(src)/shift_cipher.cpp
	$(compiler) $(flags) $^ -o $@

caesar_cipher: $(bin)/substitution.o $(bin)/affine.o $(bin)/shift.o \
		$(bin)/caesar.o $(src)/caesar_cipher.cpp
	$(compiler) $(flags) $^ -o $@

vigenere_cipher: $(bin)/vigenere.o $(src)/vigenere_cipher.cpp
	$(compiler) $(flags) $^ -o $@

$(bin)/substitution.o: $(src)/subst/substitution.cpp 
	$(compiler) $(flags) -c $^ -o $@

$(bin)/affine.o: $(src)/affine/affine.cpp 
	$(compiler) $(flags) -c $^ -o $@

$(bin)/shift.o: $(src)/shift/shift.cpp 
	$(compiler) $(flags) -c $^ -o $@

$(bin)/caesar.o: $(src)/caesar/caesar.cpp 
	$(compiler) $(flags) -c $^ -o $@

$(bin)/vigenere.o: $(src)/vigenere/vigenere.cpp 
	$(compiler) $(flags) -c $^ -o $@

clean:
	rm -f $(files)
	rm -f $(bin)/*.o

rm_files:
	rm -f cipher key decrypted
