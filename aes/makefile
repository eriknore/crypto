flags = -Wall
compiler = gcc

all: aes_128

run: aes_128
	./aes_128

remake: clean aes_128

aes_128: aes_128.o main.c
	$(compiler) $(flags) $^ -o $@

aes_128.o: aes_128.c
	$(compiler) $(flags) $^ -c -o $@

clean:
	rm -f *.o aes_128