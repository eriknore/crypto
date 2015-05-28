#include "aes_128.h"
#include "lookup_tables.h" // these are sbox, Rcon and Galois_x

/**
 * http://en.wikipedia.org/wiki/Advanced_Encryption_Standard
 * Encrypts a data block (state) of 128 bits according
 * to AES (Rijndael). Expected that key is present in 
 * AES_128.key and the block to encrypt is in AES_128.state.
 * Result after encryption is found in AES_128.state.
 */
void encrypt_128(struct AES_128 * aes) {
    // Initial round
    expand_key(aes);
    add_round_key(aes, 0);
  
    // 10 cycles of repetition
    int round;
    for(round = 1; round < 10; ++round) {
        sub_bytes(aes->state);
        shift_rows(aes->state);
        mix_columns(aes->state);
        add_round_key(aes, round);
    }

    // Final round
    sub_bytes(aes->state);
    shift_rows(aes->state);
    add_round_key(aes, 10);
}

/**
  * http://en.wikipedia.org/wiki/Rijndael_key_schedule
  * Round keys are derived from the cipher key using Rijndael's 
  * key schedule where the original key is expanded.
  */
void expand_key(struct AES_128 * aes) {
    int rcon_iter = 1;

    // first part of expanded key is copy of key
    memcpy(aes->expanded_key, aes->key, 16);

    int r;
    int c;
    // After duplication of key, 40 bytes of expanded key remains
    for(r = 4; r < 44; ++r) {
        byte temp[4];
        // copy previous 4 bytes of expanded_key to temp
        memcpy(temp, aes->expanded_key[r-1], 4);
        // Apply core for every 16 bytes
        if(r % 4 == 0)
            key_schedule_core(temp, rcon_iter++);
        // XOR with the 4-byte block 16 bytes before current index
        for(c = 0; c < 4; ++c)
            aes->expanded_key[r][c] = aes->expanded_key[r-4][c] ^ temp[c];
    }

}

/**
  * Each byte of the state is XORed with a block of the round key
  * from the expanded key.
  */
void add_round_key(struct AES_128 * aes, int round) {
    int r; int c;
    for(r = 0; r < 4; ++r)
        for(c = 0; c < 4; ++c)
            aes->state[r][c] ^= aes->expanded_key[4*round+r][c];
}

/**
  * http://en.wikipedia.org/wiki/Rijndael_S-box
  * A non-linear substitution of each byte, substitution value
  * is from a pre calculated lookup table.
  */
void sub_bytes(byte state[4][4]) {
    int r; int c;
    for(r = 0; r < 4; ++r)
        for(c = 0; c < 4; ++c)
            state[r][c] = sbox[state[r][c]];

}
/**
  * The last three rows of the state are shifted cyclically a
  *certain number of steps: 
  * row 0, 0 steps; row 1, 1 step; row 2, 2 steps; row 3, 3 steps;
  * --------------------------------------------------------------
  * Hard coded, but works for now. Not beautiful but fast :)
  * Won't work with AES_256, AES_512 
  * Note that state is transposed! Shifts are columnwise  
  */
void shift_rows(byte state[4][4]) {
    byte temp = state[0][1];
    state[0][1] = state[1][1];
    state[1][1] = state[2][1];
    state[2][1] = state[3][1];
    state[3][1] = temp;

    temp = state[1][2];
    state[1][2] = state[3][2];
    state[3][2] = temp;
    temp = state[0][2];
    state[0][2] = state[2][2];
    state[2][2] = temp;

    temp = state[2][3];
    state[2][3] = state[1][3];
    state[1][3] = state[0][3];
    state[0][3] = state[3][3];
    state[3][3] = temp;
}

/**
  * http://en.wikipedia.org/wiki/Rijndael_mix_columns
  * Operation which mixes the columns of the state, combining 
  * the four bytes in each column.
  * Instead of doing multiplication in Rijndael's Galois field 
  * pre calculated lookup tables are used.
  * --------------------------------------------------------------
  * Note that state is transposed!
  */
void mix_columns(byte state[4][4]) {
    byte temp[4][4];
    int i;
    for(i = 0; i < 4; ++i) {
        //    b_0  = 2*a_0                 + 3*a_1                 + a_2         + a_3
        temp[i][0] = Galois_2[state[i][0]] ^ Galois_3[state[i][1]] ^ state[i][2] ^ state[i][3];
        //    b_1  = a_0         + 2*a_1                 + 3*a_2                 + a_3
        temp[i][1] = state[i][0] ^ Galois_2[state[i][1]] ^ Galois_3[state[i][2]] ^ state[i][3];
        //    b_2  = a_0         + a_1         + 2*a_2                 + 3*a_3
        temp[i][2] = state[i][0] ^ state[i][1] ^ Galois_2[state[i][2]] ^ Galois_3[state[i][3]];
        //    b_3  = 3*a_0                 + a_1         + a_2         + 2*a_3 
        temp[i][3] = Galois_3[state[i][0]] ^ state[i][1] ^ state[i][2] ^ Galois_2[state[i][3]];
    }

    memcpy(state, temp, 16);

}

/**
  * Implementation of Rijndael key schedule.
  * http://en.wikipedia.org/wiki/Rijndael_key_schedule
  *
  * http://en.wikipedia.org/wiki/Rijndael_S-box
  * The Rijndael key schedule uses the Rijndael substitution box.
  * A lookup table is used instead of performing calculations
  *
  * http://en.wikipedia.org/wiki/Rijndael_key_schedule#Rcon
  * Rcon is the exponentiation of 2 to a specific value. This operation
  * is performed in Rijndael's finite field, GF(2^8). A pre calculated
  * lookup table is used instead of performing calculations.
  */
void key_schedule_core(byte row[4], int iter) {
    rotate(row);
    int r;
    for(r = 0; r < 4; ++r)
        row[r] = sbox[row[r]];
    row[0] = row[0] ^ Rcon[iter];
}

/**
  * Rotates a 32-bit word:
  * 01 23 45 67 -> 23 45 67 01 (hex)
  */
void rotate(byte row[4]) {
    byte temp = row[0];
    int r;
    for(r = 1; r < 4; ++r)
        row[r-1] = row[r];
    row[3] = temp;
}