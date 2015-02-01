#ifndef CIPHER_CAESAR_H
#define CIPHER_CAESAR_H

#include "../shift/shift.h"
#include <string>

namespace crypto {

    class Caesar_cipher : public Shift_cipher {
        
    public:
        std::string encrypt(const std::string&);
        std::string decrypt(const std::string&);

    };
}

#endif //CIPHER_CAESAR_H