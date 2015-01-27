#ifndef CYPHER_SHIFT_H
#define CYPHER_SHIFT_H

#include <string>
#include <sstream>

namespace crypto {
    class Shift_cipher {
        static const char cap_letters[], letters[];
        const int shift;

    public:
        Shift_cipher(const int&);
        std::string encrypt(const std::string&);
        std::string decrypt(const std::string&);

    };
}

#endif //CYPHER_SHIFT_H