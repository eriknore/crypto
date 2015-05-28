#include "vigenere.h"

using namespace constants; // alphabet-variables

namespace crypto {

    std::string Vigenere_cipher::encrypt(const std::string& input, const std::string& key) {
        uint key_length = key.length();
        uint input_length = input.length();
        std::stringstream ss;
        uint i = 0;
        while(i < input_length) {
            int inp_index;
            int key_index = i % key_length;
            if(input[i] == ' ')
                inp_index = size_of_alphabet - 1;
            else 
                inp_index = static_cast<int>(input[i] - 'a');
            if(inp_index < 0 || inp_index >= size_of_alphabet) { // not a valid char
                ++i; continue;    
            }
            int crypt_index = inp_index + static_cast<int>(key[key_index] - 'a');
            crypt_index = crypt_index % size_of_alphabet;
            ss << alphabet[crypt_index];
            ++i;
        }
        return ss.str();
    }

    std::string Vigenere_cipher::decrypt(const std::string& input, const std::string& key) {
        uint key_length = key.length();
        uint input_length = input.length();
        std::stringstream ss;
        uint i = 0;
        while(i < input_length) {
            int inp_index;
            int key_index = i % key_length;
            if(input[i] == ' ')
                inp_index = size_of_alphabet - 1;
            else 
                inp_index = static_cast<int>(input[i] - 'a');
            if(inp_index < 0 || inp_index >= size_of_alphabet) { // not a valid char
                ++i; continue;    
            }
            int crypt_index = inp_index - static_cast<int>(key[key_index] - 'a');
            crypt_index = (size_of_alphabet + crypt_index) % size_of_alphabet;
            ss << alphabet[crypt_index];
            ++i;
        }
        return ss.str();
    }

}