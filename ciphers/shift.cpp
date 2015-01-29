#include "shift.h"



#include <iostream>

namespace crypto {

    const char Shift_cipher::letters[] = {'a','b','c','d','e','f','g','h',
                                          'i','j','k','l','m','n','o','p',
                                          'q','r','s','t','u','v','w','x',
                                          'y','z',' '};

    std::string Shift_cipher::encrypt(const std::string& input, const uint& shift) {
        uint size_of_alphabet = sizeof(letters);
        std::stringstream ss;
        for(const char& c : input){
            int index;
            if(c == ' ')
                index = size_of_alphabet+shift-1;
            else
                index = (static_cast<int>(c)-static_cast<int>('a')+shift);
            index = (index % size_of_alphabet);
            ss << letters[index];
        }

        return ss.str();
    }

    std::string Shift_cipher::decrypt(const std::string& input, const uint& shift) {
        uint size_of_alphabet = sizeof(letters);
        std::stringstream ss;
        for(const char& c : input){
            int index;
            if(c == ' ')
                index = size_of_alphabet-shift-1;
            else
                index = (static_cast<int>(c)-static_cast<int>('a')-shift);
            // avoids being negative
            index = (size_of_alphabet+ index) % size_of_alphabet;
            ss << letters[index];
        }

        return ss.str();
    }

    std::string Shift_cipher::crack(const std::string& input, const Dictionary& d) {
        //std::cerr << "Trying shift cipher, bruteforce:" << std::endl;

        // Testing if input is already plain text
        if(d.is_english(input))
            return "Input was already in plaintext:\n"+input; 

        uint size_of_alphabet = sizeof(letters);
        std::string candidate;
        std::stringstream ss;
        for(uint i = 1; i < size_of_alphabet; ++i) {
            //std::cerr << "Trying key: " << i << std::endl;
            candidate = decrypt(input, i);
            if(d.is_english(candidate)){
                ss << "Cipher found: shift cipher, using key: " << i;
                ss << ", cipher in plaintext:\n" << candidate << std::endl;
                break;
            }
        }
        if(ss.peek() == EOF)
            return "Not Found";
        return ss.str();
    }
}