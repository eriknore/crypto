#include "caesar/caesar.h"
#include <string>
#include <iostream>
#include <algorithm>

using namespace crypto;

std::string get_input() {
    std::string line;
    std::getline(std::cin, line);
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
    return line;
}

int main(int argc, char* argv[]) {
    bool ok = false;
    std::string arg1;
    std::string processed;
    switch(argc) {
        case 2: 
            {   
                // Caesar cipher is shift cipher with K = 3
                arg1 = std::string(argv[1]);
                Caesar_cipher caesar;
                std::string input = get_input();
                if(arg1 == "-e" || arg1 == "-encrypt") {
                    processed = caesar.encrypt(input);
                    ok = true;
                    break;
                } else if(arg1 == "-d" || arg1 == "-decrypt"){
                    processed = caesar.decrypt(input);
                    ok = true;
                    break;
                }
                // unknown command -> fall through
            }
        default: 
            {
                std::cerr << "usage: caesar_cipher <mode>\n";
                std::cerr << "\nPossible modes:\n";
                std::cerr << "   -e -encrypt     encrypts input from stdin\n";
                std::cerr << "   -d -decrypt     decrypts input from stdin\n\n";
                std::cerr << "Typical usage:\n";
                std::cerr << "   caesar_cipher -e < plain > cipher\n";
                std::cerr << "   caesar_cipher -d < cipher > decrypted\n";
                std::cerr << "where plain is a file containg plaintext and cipher\n";
                std::cerr << "will be written to/read from the file cipher\n" << std::endl;
            }
    }

    if(ok) {
        if(arg1 == "-e" || arg1 == "-encrypt")
            std::transform(processed.begin(), processed.end(), processed.begin(), ::toupper);
        std::cout << processed << std::endl;
    }

    return 0;
}