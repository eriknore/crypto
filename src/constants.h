#ifndef CRYPTO_CONST_H
#define CRYPTO_CONST_H

#include <cstdlib>

namespace constants {

    static const char alphabet[] = {'a','b','c','d','e','f','g','h','i',
                                    'j','k','l','m','n','o','p','q','r',
                                    's','t','u','v','w','x','y','z',' '};
    static const std::size_t size_of_alphabet = sizeof(alphabet);

    // Used in e.g. Affine cipher where shift is decided using formula
    // shift = (a + b) % size_of_alphabet where 'a' must be a primitive
    // root of a. The following is correct for size_of_alphabet == 27
    static const int accepted_a[] = {1,2,5,7,11,13,17,19,23};
    static const int nr_of_as = sizeof(accepted_a)/sizeof(int);

}

#endif // CRYPTO_CONST_H