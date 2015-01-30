#include "../tools/dictionary/dictionary.h"
#include "../ciphers/shift.h"
#include <iostream>
#include <string>
#include <sstream>
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
                std::srand(std::time(0)); //use current time as seed for random generator
                int shift = std::rand() % 26; // alphabet is a-z plus space, zero-indexed
                Shift_cipher sc;
                std::string input = get_input();
                if(arg1 == "-e" || arg1 == "-encrypt") {
                    processed = sc.encrypt(input, shift);
                    std::cerr << shift << std::endl;
                } else if(arg1 == "-d" || arg1 == "-decrypt")
                    processed = sc.decrypt(input, shift);
                else // unknown command
                    break;
                ok = true;
                break;
            }
        case 3: 
            {   
                arg1 = std::string(argv[1]);
                int shift = atoi(argv[2]);
                Shift_cipher sc;
                std::string input = get_input();
                if(arg1 == "-e" || arg1 == "-encrypt")
                    processed = sc.encrypt(input, shift);
                else if(arg1 == "-d" || arg1 == "-decrypt")
                    processed = sc.decrypt(input, shift);
                else // unknown command
                    break;
                ok = true;
                break;
            }
        default: 
            {
                std::cerr << "usage: shift_cipher <mode> [<shifts>]\n";
                std::cerr << "\nPossible modes:\n";
                std::cerr << "   -e -encrypt     encrypts input from stdin\n";
                std::cerr << "   -d -decrypt     decrypts input from stdin\n\n";
                std::cerr << "shifts is the number of shifts used for encryption/decryption.\n";
                std::cerr << "If left empty it will be randomized and key will be written to\n";
                std::cerr << "stderr. Note that this applies for decryption as well!\n\n";
                std::cerr << "Typical usage:\n";
                std::cerr << "   shift_cipher -e 12 < plain > cipher\n";
                std::cerr << "   shift_cipher -d 12 < cipher > decrypted\n";
                std::cerr << "   shift_cipher -e < plain > cipher 2> key\n";
                std::cerr << "where plain is a file containg plaintext and cipher/key/decrypted\n";
                std::cerr << "will be written to respective file\n" << std::endl;
            }
    }

    if(ok) {
        if(arg1 == "-e" || arg1 == "-encrypt")
            std::transform(processed.begin(), processed.end(), processed.begin(), ::toupper);
        std::cout << processed << std::endl;
    }
    return 0;
}