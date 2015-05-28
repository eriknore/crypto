#ifndef AES_MAIN
#define AES_MAIN

#include "aes_128.h"
#include "stdio.h"

int main() {
    struct AES_128 aes;
    fread(aes.key, 4, 4, stdin); // 4*4 bytes
    while(!feof(stdin)) {
        fread(aes.state, 4, 4, stdin);
        if(!feof(stdin)) {
            encrypt_128(&aes);
            fwrite(aes.state, 4, 4, stdout);
        }
    }
    return 0;
}

#endif // AES_MAIN