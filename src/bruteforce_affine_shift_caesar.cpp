#include "../helper-tools/dictionary/dictionary.h"
#include "../src/affine/affine.h"
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
    uint nr_of_accepted_as = sizeof(accepted_a);
    for(uint i = 0; i < nr_of_accepted_as && !found; ++i) {
        for(uint j = 0; j < size_of_alphabet && !found; ++j) {
            candidate = aff.decrypt(input, i, j);
            if(d.is_english(candidate)){
                std::string cipher_used;
                if(i == 0) // special case when a == 1
                    if(j == 3) // special case when b == 3
                        cipher_used = "Caesar Cipher";
                    else
                        cipher_used = "Shift Cipher";
                else
                    cipher_used = "Affine Cipher";

                ss << "Cipher used: " << cipher_used << ", using key: ";
                ss << i << "\nCipher in plaintext:\n\n" << candidate;
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
    std::cout << "Input cipher:\n >";
    // cryptanalysis
    std::string input = get_input();
    std::string processed = bruteforce(input);
    std::cout << processed << std::endl;

    return 0;
}