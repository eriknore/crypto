flags = -std=c++11 -Wall
compiler = clang++
files = bruteforce ngrams ic_calc subst_cipher crack_viginere
c_sub = crack_subst
c_vig = crack_vigenere
bin = ../bin
src = ../src
tools = ../helper-tools

all: $(files)

remake: clean $(files)

bruteforce: $(bin)/dictionary.o $(bin)/substitution.o $(bin)/affine.o \
			$(src)/bruteforce_affine_shift_caesar.cpp
	$(compiler) $(flags) $^ -o $@

ngrams: FORCE
	$(MAKE) -C $(tools)/ngrams
	cp $(tools)/ngrams/ngrams $(c_sub)/ngrams

ic_calc: $(bin)/ic_calc.o $(tools)/IC_calc/ic_calc_main.cpp
	$(compiler) $(flags) $^ -o $(c_sub)/$@

subst_cipher: $(bin)/substitution.o $(src)/subst_cipher.cpp
	$(compiler) $(flags) $^ -o $(c_sub)/$@

crack_viginere: $(bin)/ic_calc.o $(bin)/vigenere.o $(src)/crack_vigenere.cpp
	$(compiler) $(flags) $^ -o $(c_vig)/$@

$(bin)/dictionary.o: $(tools)/dictionary/dictionary.cpp 
	$(compiler) $(flags) -c $^ -o $@

$(bin)/substitution.o: $(src)/subst/substitution.cpp 
	$(compiler) $(flags) -c $^ -o $@

$(bin)/affine.o: $(src)/affine/affine.cpp 
	$(compiler) $(flags) -c $^ -o $@

$(bin)/ic_calc.o: $(tools)/IC_calc/ic_calc.cpp
	$(compiler) $(flags) -c $^ -o $@

$(bin)/vigenere.o: $(src)/vigenere/vigenere.cpp 
	$(compiler) $(flags) -c $^ -o $@

FORCE:

clean:
	rm -f bruteforce $(c_sub)/ngrams $(c_sub)/ic_calc \
								$(c_sub)/subst_cipher
