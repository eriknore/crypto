#ifndef CIPHER_SUBST_H
#define CIPHER_SUBST_H

#include <string>
#include <vector>
#include "../resources/dictionary.h"
#include <chrono>

namespace crypto {

    class Subst_cipher {
        static const char letters[];
        std::vector<int> permutation;

    public:
        Subst_cipher();
        Subst_cipher(const std::vector<int>&);
        std::string encrypt(const std::string&);
        std::string decrypt(const std::string&);
        std::string crack(const std::string&, const Dictionary&);
        std::string get_permutation() const;
        bool set_permutation(std::string);
        int get_size_of_alphabet() const;

    };
}

#endif //CIPHER_SUBST_H