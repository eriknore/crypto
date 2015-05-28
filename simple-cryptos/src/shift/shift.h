#ifndef CIPHER_SHIFT_H
#define CIPHER_SHIFT_H

#include "../affine/affine.h"
#include <string>

namespace crypto {

    class Shift_cipher : public Affine_cipher {
        
    public:
        std::string encrypt(const std::string&, const int&);
        std::string decrypt(const std::string&, const int&);

    };
}

#endif //CIPHER_SHIFT_H