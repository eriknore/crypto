#ifndef CIPHER_SHIFT_H
#define CIPHER_SHIFT_H

#include <string>
#include <sstream>
#include "../resources/dictionary.h"

namespace crypto {

    class Shift_cipher {
        static const char letters[];

    public:
        std::string encrypt(const std::string&, const uint&);
        std::string decrypt(const std::string&, const uint&);
        std::string crack(const std::string&, const Dictionary&);

    };
}

#endif //CIPHER_SHIFT_H