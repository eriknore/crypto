#include "resources/dictionary.h"
#include <iostream>
#include <string>

using namespace crypto;

void encrypt() {
    std::cout << "Encrypting..." << std::endl;
}

void decrypt() {
    std::cout << "Decrypting..." << std::endl;   
}

void cryptanalysis() {
    std::cout << "Cracking crypto..." << std::endl;
}

int main(int argsc, char* argsv[]) {
    switch(argsc) {
        case 2: 
            {   
                const std::string& arg(argsv[1]);
                if(arg == "-e" || arg == "-encrypt") {
                    encrypt();
                    break;
                } else if(arg == "-d" || arg == "-decrypt") {
                    decrypt();
                    break;
                } else if(arg == "-crack") {
                    cryptanalysis();
                    break;
                }
            }
        default: 
            {
                std::cerr << "USAGE: crypto -e[ncrypt]||-d[ecrypt]" << std::endl;
            }
    } 

    std::cout << "\n\nDictionary Test: " << std::endl;
    Dictionary d;
    bool answer = d.is_a_word("potatis");
    std::cout << "Dictionary contains 'potatis'?\n- ";
    if(answer) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }
    return 0;
}

