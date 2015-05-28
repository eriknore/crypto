#include "../helper-tools/dictionary/dictionary.h"
#include "../src/affine/affine.h"
#include "../src/constants.h"
#include <iostream>
#include <string>

using namespace crypto;
using namespace constants;

std::string bruteforce(const std::string& input) {
    Dictionary d;
    // Testing if input is already plain text
    if(d.is_english(input))
        return "Input was already in plaintext:\n"+input; 
    Affine_cipher aff;
    std::string candidate;
    std::stringstream ss;
    bool found = false;
    for(uint i = 0; i < nr_of_as && !found; ++i) {
        for(uint j = 0; j < size_of_alphabet && !found; ++j) {
            candidate = aff.decrypt(input, accepted_a[i], j);
            if(d.is_english(candidate)){
                std::string cipher_used;
                if(i == 0) { // SHIFT: special case of AFFINE when a == 1
                    if(j == 3) {// CAESAR: special case of SHIFT when b == 3
                        ss << "Cipher used: Caesar Cipher";
                        ss << "\nCipher in plaintext:\n\n" << candidate;
                    } else {
                        ss << "Cipher used: Shift Cipher" << ", using K: ";
                        ss << j << "\nCipher in plaintext:\n\n" << candidate;
                    }
                } else {
                    cipher_used = "Affine Cipher";
                    ss << "Cipher used: Affine Cipher" << ", using key: a = ";
                    ss << accepted_a[i] << " b = " << j;
                    ss << "\nCipher in plaintext:\n\n" << candidate;
                }
                ss << std::endl;
                found = true;
            }
        }
    }
    if(ss.peek() == EOF)
        return "Not Found";
    return ss.str();
    }

std::string get_input() {
    std::string line;
    std::getline(std::cin, line);
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
    return line;
}

int main(int argc, char* argv[]) {
    std::cout << "Input cipher:\n";
    std::string input = get_input();
    std::string processed = bruteforce(input);
    std::cout << processed << std::endl;

    return 0;
}