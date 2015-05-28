flags = -std=c++11 -Wall
compiler = clang++

all:
	$(MAKE) -C ciphers
	$(MAKE) -C cryptanalysis

remake:
	$(MAKE) remake -C ciphers
	$(MAKE) remake -C cryptanalysis

ciphers:
	$(MAKE) -C ciphers

cryptanalysis:
	$(MAKE) -C cryptanalysis

clean:
	$(MAKE) clean -C ciphers
	$(MAKE) clean -C cryptanalysis
