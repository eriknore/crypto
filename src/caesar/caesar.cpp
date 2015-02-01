#include "caesar.h"

namespace crypto {

    std::string Caesar_cipher::encrypt(const std::string &input) {
        return Shift_cipher::encrypt(input, 3);
    }
    
    std::string Caesar_cipher::decrypt(const std::string &input) {
        return Shift_cipher::decrypt(input, 3);
    }

}