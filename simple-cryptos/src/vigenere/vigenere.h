#ifndef CIPHER_VIGENERE_H
#define CIPHER_VIGENERE_H

#include "../constants.h"
#include <string>
#include <sstream>

namespace crypto {

    class Vigenere_cipher {

    public:
        std::string encrypt(const std::string&, const std::string&);
        std::string decrypt(const std::string&, const std::string&);

    };
}

#endif //CIPHER_VIGENERE_H