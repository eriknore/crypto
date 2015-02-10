#ifndef AES_128_H
#define AES_128_H

#include "string.h"
typedef unsigned char byte;

struct AES_128 {
    byte key[4][4];
    byte expanded_key[11*4][4];
    byte state[4][4];
};

void encrypt_128(struct AES_128 * aes);
void expand_key(struct AES_128 * aes);
void add_round_key(struct AES_128 * aes, int round);
void sub_bytes(byte state[4][4]);
void shift_rows(byte state[4][4]);
void mix_columns(byte state[4][4]);
void key_schedule_core(byte row[4], int iter);
void rotate(byte row[4]);

#endif // AES_128_H