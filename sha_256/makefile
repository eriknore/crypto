flags = -g -O2 -std=gnu99 -static -lm
compiler = gcc

all: sha256

run: sha256
	./sha256

remake: clean sha256

sha256: sha256.c
	$(compiler) $(flags) $^ -o $@

clean:
	rm -f *.o sha256