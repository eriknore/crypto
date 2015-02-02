#ifndef CRYPTO_ICCALC_H
#define CRYPTO_ICCALC_H

#include <string>
#include "../../src/constants.h"

namespace crypto {

    struct IC_calc {
        double calculate(const std::string &);
    };
}

#endif // CRYPTO_ICCALC_H