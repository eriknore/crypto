#include "../tools/dictionary/dictionary.h"
#include "../ciphers/shift.h"
#include <iostream>
#include <string>

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
                const std::string& arg1(argv[1]);
                if(arg1 == "-c" || arg1 == "-crack") {
                    // cryptanalysis
                    std::string input = get_input();
                    Dictionary english;
                    Shift_cipher sc;
                    std::string processed = sc.crack(input, english);
                    std::cout << processed << std::endl;
                    break;
                }
            }
        default: 
            {
                std::cerr << "usage: crack_shift <mode>\n";
                std::cerr << "\nPossible modes:\n";
                std::cerr << "   -c -crack     attempts to crack input from stdin\n\n";
                std::cerr << "Exhaustive key search (26 shifts)\n\n";
                std::cerr << "Typical usage:\n";
                std::cerr << "   crack_shift -c < cipher > decrypted\n";
                std::cerr << "where cipher is a file containg ciphertext and all output\n";
                std::cerr << "is written to decrypted\n" << std::endl;
            }   
    }

    return 0;
}