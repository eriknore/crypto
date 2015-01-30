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
        for(const char &c : input){
            int letter_nr;
            if(c == ' ')
                letter_nr = size_of_alphabet-1;
            else {
                letter_nr = static_cast<int>(c - 'a');
            }
            if(letter_nr < 0 || letter_nr > 26) // ie. not a-z or space
                continue;
            letter_nr = (letter_nr + shift) % size_of_alphabet;
            ss << letters[letter_nr];
        }

        return ss.str();
    }

    std::string Shift_cipher::decrypt(const std::string& input, const uint& shift) {
        uint size_of_alphabet = sizeof(letters);
        std::stringstream ss;
        for(const char& c : input){
            int letter_nr;
            if(c == ' ')
                letter_nr = size_of_alphabet-1;
            else {
                letter_nr = static_cast<int>(c - 'a');
            }
            if(letter_nr < 0 || letter_nr > 26) // ie. not a-z or space
                continue;
            // avoids being negative
            letter_nr = (size_of_alphabet + letter_nr - shift) % size_of_alphabet;
            ss << letters[letter_nr];
        }

        return ss.str();
    }

    std::string Shift_cipher::crack(const std::string& input, const Dictionary& d) {
        // Testing if input is already plain text
        if(d.is_english(input))
            return "Input was already in plaintext:\n"+input; 

        uint size_of_alphabet = sizeof(letters);
        std::string candidate;
        std::stringstream ss;
        // Try all shifts starting from 1
        for(uint i = 1; i < size_of_alphabet; ++i) {
            candidate = decrypt(input, i);
            if(d.is_english(candidate)){
                ss << "Cipher used: shift cipher, using key: " << i;
                ss << "\nCipher in plaintext:\n\n" << candidate << std::endl;
                break;
            }
        }
        if(ss.peek() == EOF)
            return "Not Found";
        return ss.str();
    }
}