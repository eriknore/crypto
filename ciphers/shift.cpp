#include "shift.h"



#include <iostream>

namespace crypto {

    const char Shift_cipher::cap_letters[] = {'A','B','C','D','E','F','G',
                                              'H','I','J','K','L','M','N',
                                              'O','P','Q','R','S','T','U',
                                              'V','W','X','Y','Z',' '};

    const char Shift_cipher::letters[] = {'a','b','c','d','e','f','g','h',
                                          'i','j','k','l','m','n','o','p',
                                          'q','r','s','t','u','v','w','x',
                                          'y','z',' '};

    Shift_cipher::Shift_cipher(const int& shift) : shift(shift) {};

    std::string Shift_cipher::encrypt(const std::string& input) {
        uint size_of_alphabet = sizeof(cap_letters);
        std::stringstream ss;
        for(const char& c : input){
            int index;
            if(c == ' ')
                index = size_of_alphabet+shift-1;
            else
                index = (static_cast<int>(c)-static_cast<int>('a')+shift);
            index = (index % size_of_alphabet);
            ss << cap_letters[index];
        }

        return ss.str();
    }

    std::string Shift_cipher::decrypt(const std::string& input) {
        uint size_of_alphabet = sizeof(letters);
        std::stringstream ss;
        for(const char& c : input){
            int index;
            if(c == ' ')
                index = size_of_alphabet-shift-1;
            else
                index = (static_cast<int>(c)-static_cast<int>('A')-shift);
            // avoid being negative
            index = (size_of_alphabet+ index) % size_of_alphabet;
            ss << letters[index];
        }

        return ss.str();
    }
}