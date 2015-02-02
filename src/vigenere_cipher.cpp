#include "vigenere/vigenere.h"
#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>

using namespace crypto;

std::string get_input() {
    std::string line;
    std::getline(std::cin, line);
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
    return line;
}

int main(int argc, char* argv[]) {
    switch(argc) {
        case 2:
            {
                std::string arg1(argv[1]);
                Vigenere_cipher vig;
                std::string key = get_input();
                std::string input = get_input();
                std::string processed;
                if(arg1 == "-d" || arg1 == "-decrypt")
                    processed = vig.decrypt(input, key);
                else if(arg1 == "-e" || arg1 == "-encrypt") {
                    processed = vig.encrypt(input, key);
                    std::transform(processed.begin(), processed.end(), processed.begin(), ::toupper);
                    std::cerr << key << std::endl;
                }
                std::cout << processed << std::endl;
                break;
            }
        case 3:
            {
                std::string arg1(argv[1]);
                std::string key(argv[2]);
                Vigenere_cipher vig;
                std::string input = get_input();
                std::string processed;
                if(arg1 == "-d" || arg1 == "-decrypt")
                    processed = vig.decrypt(input, key);
                else if(arg1 == "-e" || arg1 == "-encrypt") {
                    processed = vig.encrypt(input, key);
                    std::transform(processed.begin(), processed.end(), processed.begin(), ::toupper);
                    std::cerr << key << std::endl;
                }
                std::cout << processed << std::endl;
                break;
            }
        default: 
            {
                std::cerr << "usage: subst_cipher <mode>\n";
                std::cerr << "\nPossible modes:\n";
                std::cerr << "   -e -encrypt     encrypts input from stdin\n";
                std::cerr << "   -d -decrypt     decrypts input from stdin\n\n";
                std::cerr << "For encryption, a random key is used and is output on stderr in the\n";
                std::cerr << "expected format (see below). For decryption, a key is expected on\n";
                std::cerr << "stdin before the cipher text. The expected format of the key is:\n\n";
                std::cerr << "[   Z Y X W V U T S R Q P O N M L K J I H G F E D C B A ]\n";
                std::cerr << "   (in this example 'a' is mapped to ' ' (space),\n";
                std::cerr << "    'b' to 'Z', 'c' to 'Y', ... 'z' to 'A')\n\n";
                std::cerr << "Typical usage:\n";
                std::cerr << "   ./subst_cipher -e < plain > cipher 2> key\n";
                std::cerr << "   cat key cipher | ./subst_cipher -d > decrypted\n";
                std::cerr << "\nwhere plain is a file containg plaintext and cipher/key/decrypted\n";
                std::cerr << "will be written to respective file with expected content\n" << std::endl;
            }
    }

    return 0;
}