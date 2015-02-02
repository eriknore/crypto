flags = -std=c++11 -Wall
compiler = clang++
files = bruteforce ngrams ic_calc subst_cipher
c_sub = crack_subst
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

ic_calc: $(tools)/IC_calc/ic_calc.cpp
	$(compiler) $(flags) $^ -o $(c_sub)/$@

subst_cipher: $(bin)/substitution.o $(src)/subst_cipher.cpp
	$(compiler) $(flags) $^ -o $(c_sub)/$@

$(bin)/dictionary.o: ../helper-tools/dictionary/dictionary.cpp 
	$(compiler) $(flags) -c $^ -o $@

$(bin)/substitution.o: $(src)/subst/substitution.cpp 
	$(compiler) $(flags) -c $^ -o $@

$(bin)/affine.o: $(src)/affine/affine.cpp 
	$(compiler) $(flags) -c $^ -o $@

FORCE:

clean:
	rm -f bruteforce $(c_sub)/ngrams $(c_sub)/ic_calc \
								$(c_sub)/subst_cipher
