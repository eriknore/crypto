#ifndef CIPHER_SUBST_H
#define CIPHER_SUBST_H

#include "../constants.h"
#include <string>
#include <vector>
#include <chrono>
#include <sstream>

namespace crypto {

    class Subst_cipher {
        std::vector<int> permutation;

    public:
        Subst_cipher();
        Subst_cipher(const std::vector<int>&);
        std::string encrypt(const std::string&);
        std::string decrypt(const std::string&);
        std::string get_permutation() const;
        bool set_permutation(std::string);

    };
}

#endif //CIPHER_SUBST_H