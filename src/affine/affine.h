#ifndef CIPHER_AFFINE_H
#define CIPHER_AFFINE_H

#include "../subst/substitution.h"
#include "../constants.h"
#include <string>
#include <unordered_set>
#include <algorithm>

namespace crypto {

    class Affine_cipher : public Subst_cipher {
        bool a_is_accepted(const int&) const;
    protected:
        void set_permutation(const int&, const int&);

    public:
        std::string encrypt(const std::string&, const int&, const int&);
        std::string decrypt(const std::string&, const int&, const int&);

    };
}

#endif //CIPHER_AFFINE_H