flags = -std=c++11 -Wall
compiler = clang++

all: ciphers

remake: clean

ciphers:
	$(MAKE) -C ciphers

cryptanalysis: FORCE
	cd cryptanalysis && make

FORCE:

clean:
	$(MAKE) clean -C ciphers
	#cd cryptanalysis && make clean
