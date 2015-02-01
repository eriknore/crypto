#include "shift.h"

namespace crypto {

    std::string Shift_cipher::encrypt(const std::string &input, const int &b) {
        return Affine_cipher::encrypt(input, 1, b);
    }
    
    std::string Shift_cipher::decrypt(const std::string &input, const int& b) {
        return Affine_cipher::decrypt(input, 1, b);
    }

}