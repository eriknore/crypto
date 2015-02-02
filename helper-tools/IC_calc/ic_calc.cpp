#include "ic_calc.h"

using namespace constants; // alphabet variables

namespace crypto {
    double IC_calc::calculate(const std::string &input) {
        int freqs[size_of_alphabet]; // a-z
        uint nr_of_chars = 0;
        for(uint i = 0; i < size_of_alphabet; ++i)
            freqs[i] = 0;
        for(const char &c : input) {
            int letter_nr = static_cast<int>(c - 'a');
            if(letter_nr < 0 || letter_nr > 25) // ie. not a-z
                continue;
            ++freqs[letter_nr];
            ++nr_of_chars;
        }
        double ic_result = 0;
        for(uint i = 0; i < 26; ++i)
            ic_result += freqs[i]*(freqs[i]-1);
        return ic_result / (nr_of_chars*(nr_of_chars-1));
    }
}