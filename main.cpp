#include "resources/dictionary.h"
#include "ciphers/shift.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace crypto;

void cryptanalysis() {
    std::cout << "Cracking crypto..." << std::endl;
}

std::string get_input(const std::string& type) {
    std::string line;
    std::getline(std::cin, line);
    return line;
}

int main(int argc, char* argv[]) {
    switch(argc) {
        case 4: 
            {   
                const std::string& arg(argv[1]);
                const std::string& arg2(argv[2]);
                if(arg == "-e" || arg == "-encrypt") {
                    if(arg2 == "shift") {
                        int shift = atoi(argv[3]);
                        Shift_cipher sc(shift);
                        std::string encrypted = sc.encrypt(get_input("encrypt"));
                        std::cout << encrypted << std::endl;
                    }
                    break;
                } else if(arg == "-d" || arg == "-decrypt") {
                    if(arg2 == "shift") {
                        int shift = atoi(argv[3]);
                        Shift_cipher sc(shift);
                        std::string decrypted = sc.decrypt(get_input("decrypt"));
                        std::cout << decrypted << std::endl;
                    }
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

    return 0;
}

