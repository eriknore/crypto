#include "resources/dictionary.h"
#include "ciphers/shift.h"
#include "ciphers/substitution.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace crypto;


void cryptanalysis() {
    std::cout << "Cracking crypto..." << std::endl;
}

std::string get_input() {
    std::string line;
    std::getline(std::cin, line);
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
    return line;
}

void count_IC() {
    std::string input = get_input();
    int freqs[26]; // a-z
    int tot_count = 0;
    for(uint i = 0; i < 26; ++i)
        freqs[i] = 0;
    for(const char &c : input) {
        int letter_nr = static_cast<int>(c - 'a');
        if(letter_nr < 0 || letter_nr > 25) // ie. not a-z
            continue;
        ++freqs[letter_nr];
        ++tot_count;
    }
    double sum = 0;
    for(uint i = 0; i < 26; ++i)
        sum += freqs[i]*(freqs[i]-1);
    double ic = sum / (tot_count*(tot_count-1));
    std::cerr << "IC = " << ic << "   nr of chars = " << tot_count << std::endl;
}

int main(int argc, char* argv[]) {
    switch(argc) {
        case 2:
            {
                const std::string& arg1(argv[1]);
                if(arg1 == "-c" || arg1 == "-crack") {
                    // cryptanalysis
                    std::string input = get_input();
                    std::string processed;
                    Dictionary d;

                    // First try shift cipher, bruteforce
                    Shift_cipher sc;
                    processed = sc.crack(input, d);
                    std::cout << processed << std::endl;
                    break;
                }
            }
        case 3:
            {
                const std::string& arg1(argv[1]);
                const std::string& arg2(argv[2]);
                if(arg2 == "substitution") {
                    Subst_cipher sc;
                    if(arg1 == "-d" || arg1 == "-decrypt") {
                        std::cerr << "Please enter a key in the format\n";
                        std::cerr << "[ A B C ... Z ]" << std::endl;
                        if(!sc.set_permutation(get_input())) {
                            std::cerr << "Key format not accepted\nexiting..." << std::endl;
                            return -1;
                        }
                    }

                    std::string input = get_input();
                    std::string processed;
                    if(arg1 == "-d" || arg1 == "-decrypt")
                        processed = sc.decrypt(input);
                    else if(arg1 == "-e" || arg1 == "-encrypt") {
                        processed = sc.encrypt(input);
                        std::transform(processed.begin(), processed.end(), processed.begin(), ::toupper);
                        std::cout << sc.get_permutation() << std::endl;
                    }
                    std::cout << processed << std::endl;
                    break;
                }
            }
        case 4: 
            {   
                const std::string& arg1(argv[1]);
                const std::string& arg2(argv[2]);
                if(arg2 == "shift") {
                    int shift = atoi(argv[3]);
                    Shift_cipher sc;
                    std::string input = get_input();
                    std::string processed;
                    if(arg1 == "-e" || arg1 == "-encrypt")
                        processed = sc.encrypt(input, shift);
                    else if(arg1 == "-d" || arg1 == "-decrypt")
                        processed = sc.decrypt(input, shift);
                    else // unknown command
                        break;
                    if(arg1 == "-e" || arg1 == "-encrypt")
                        std::transform(processed.begin(), processed.end(), processed.begin(), ::toupper);
                    std::cout << processed << std::endl;
                    break;
                }
            }
        default: 
            {
                std::cerr << "usage: crypto <mode> [<cipher> <args>] <plaintext/cipher>" << std::endl;
                std::cerr << "\nPossible modes:" << std::endl;
                std::cerr << "   -e -encrypt     encrypts input using <cipher>" << std::endl;
                std::cerr << "   -d -decrypt     decrypts input using <cipher>" << std::endl;
                std::cerr << "   -c -crack       cryptanalysis of input" << std::endl;
                std::cerr << "                   example: crypto -c <plaintext/cipher>" << std::endl;
                std::cerr << "\nPossible ciphers:" << std::endl;
                std::cerr << "   shift x         encrypts input using shift cipher, shifting letters x steps" << std::endl;
            }   std::cerr << "                   example: crypto -e shift 11" << std::endl;
    }

    count_IC();
    return 0;
}

/* TODO:
    - Substitution cipher
    - Affine cipher
    - Vigenère cipher
    - Hill cipher
    - Permutation cipher
    - Stream cipher
    - Autokey cipher

    - statistical cryptanalysis

*/