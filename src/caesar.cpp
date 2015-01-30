#include "../tools/dictionary/dictionary.h"
#include "../ciphers/shift.h"
#include <iostream>
#include <string>
#include <chrono>

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
                arg1 = std::string(argv[1]);
                int shift = 3; // Caesar is K=3
                Shift_cipher sc;
                std::string input = get_input();
                if(arg1 == "-e" || arg1 == "-encrypt") {
                    processed = sc.encrypt(input, shift);
                } else if(arg1 == "-d" || arg1 == "-decrypt")
                    processed = sc.decrypt(input, shift);
                else // unknown command
                    break;
                ok = true;
                break;
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