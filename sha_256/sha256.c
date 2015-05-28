#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "constants.h"

/* Most of the notation is similar to main source: FIPS 180-4
 * http://csrc.nist.gov/publications/fips/fips180-4/fips-180-4.pdf
 *
 * Test cases from NIST as well
 * http://csrc.nist.gov/groups/ST/toolkit/documents/Examples/SHA256.pdf
*/

#define DEBUG 0

struct sha256_data {
	// Message in a 64-byte block matrix, 100 blocks is enough?
	uint8_t M[100][64];
	uint32_t hash[8];
	uint64_t l; // size of input in bits
};

uint32_t ROTR(uint32_t x, int n)				{ return ( ( x >> n ) | (x << 32-n) ); 					}
uint32_t SHR(uint32_t x, int n) 				{ return (x >> n); 										}
uint32_t CH(uint32_t x,uint32_t y,uint32_t z) 	{ return ( (x & y) ^ ( (~x) & z) ); 					}
uint32_t MAJ(uint32_t x,uint32_t y,uint32_t z)  { return ( (x & y) ^ (x & z) ^ (y & z) ); 				}
uint32_t SIGMA0(uint32_t x) 					{ return ( ROTR(x, 2)  ^ ROTR(x, 13) ^ ROTR(x, 22) );	}
uint32_t SIGMA1(uint32_t x) 					{ return ( ROTR(x, 6)  ^ ROTR(x, 11) ^ ROTR(x, 25) ); 	}
uint32_t sigma0(uint32_t x) 					{ return ( ROTR(x, 7)  ^ ROTR(x, 18) ^ SHR(x, 3) ); 	}
uint32_t sigma1(uint32_t x) 					{ return ( ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10) );	}

uint32_t get_uint32(uint8_t * src) {
	return ( (uint32_t) src[0] << 24 | 
			 (uint32_t) src[1] << 16 |
			 (uint32_t) src[2] << 8  |
			 (uint32_t) src[3]       );
}

// Update the struct using ptr as arg. We will also need N afterwards
// since it might need updating we pass it as a ptr as well
void perform_padding(struct sha256_data * sha256, int * N, int b) {
	// PADDING, if block full then b == 0 already
	// add 1000 0000 = 0x80 to end of message
	sha256->M[*N][b++] = 0x80;

	// block may now be too small for last size of uint64!
	if(b > 56) {
		while(b < 64)
			sha256->M[*N][b++] = 0x00;
		b = 0;
		*N = *N+1;
	}
	
	// pad the block with 0s, until last 8 bytes
	while(b < 56)
		sha256->M[*N][b++] = 0x00;

	// store the size as uint64 at last 8 bytes, reversed byte order
	for(int i = 0; i < 8; ++i)
		sha256->M[*N][56+i] = (sha256->l >> 8*(7-i));

}

void sha256_algorithm(struct sha256_data *sha256, int *N) {
	uint32_t W[64];
	uint32_t vars[8];
	uint32_t T[2];

	for(int n = 0; n <= *N; ++n) {

		// 1. Init working set of words
		for(int i = 0; i < 16; ++i)
			W[i] = get_uint32(&sha256->M[n][4*i]);

		if(DEBUG) {
			printf("\nW: ");
			for(int i = 0; i < 16; ++i)
				printf("%08x ", W[i]);
			printf("\n\n");
		}

		for(int t = 16; t < 64; ++t)
			W[t] = sigma1(W[t-2]) + W[t-7] + sigma0(W[t-15]) + W[t-16];

		// 2. Init working variables a-f
		for(int i = 0; i < 8; ++i)
			vars[i] = sha256->hash[i];

		if(DEBUG)
			printf("            a        b        c        d        e        f        g        h\n");

		// 3. Process all variables
		// a = 0 | b = 1 | c = 2 | d = 3 | e = 4 | f = 5 | g = 6 | h = 7	
		for(int t = 0; t < 64; ++t) {
			T[0] = vars[7] + SIGMA1(vars[4]) + CH(vars[4], vars[5], vars[6]) + K[t] + W[t];
			T[1] = SIGMA0(vars[0]) + MAJ(vars[0], vars[1], vars[2]);
			vars[7] = vars[6]; 			// h = g
			vars[6] = vars[5]; 			// g = f
			vars[5] = vars[4]; 			// f = e
			vars[4] = vars[3] + T[0]; 	// e = d + T1
			vars[3] = vars[2]; 			// d = c
			vars[2] = vars[1]; 			// c = b
			vars[1] = vars[0]; 			// b = a
			vars[0] = T[0] + T[1]; 		// a = T1 + T2

			if(DEBUG) {
				printf("Round %d: ", t);
				for(int i = 0; i < 8; ++i)
					printf("%08x ", vars[i]);
				printf("\n");
			}
		}

		// 4. Compute hashes
		for(int i = 0; i < 8; ++i)
			sha256->hash[i] = vars[i] + sha256->hash[i];

	}
}

int main() {
	char c[2];
	c[0] = getchar();
	while(c[0] != EOF) {
		uint8_t input;
		int b = 0; 
		int N = 0; // blocks
		struct sha256_data sha256;
		sha256.l = 0;
		
		// read from stdin until end-of-line, to message matrix
		while(c[0] != EOF && c[0] != '\n') {
			c[1] = getchar();
			sscanf(c, "%2x", &input);

			sha256.M[N][b++] = (uint8_t) input;
			sha256.l += 8; // added 1 byte = 8 bits

			if(b == 64) {
				b = 0;
				++N;
			}
			c[0] = getchar();
		}

		// init hash with H_0
		for(int i = 0; i < 8; ++i)
			sha256.hash[i] = H_0[i];


		perform_padding(&sha256, &N, b);

		// run the sha256 algorithm on all blocks
		sha256_algorithm(&sha256, &N);

		if(DEBUG) { printf("\n"); } // nicer debug print

		// When finished, print the hash
		for(int i = 0; i < 8; ++i)
			printf("%08x", sha256.hash[i]);
		printf("\n");

		// read next char: either start of new string or EOF
		c[0] = getchar();
	}

	return 0;
}