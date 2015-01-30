#include "../ciphers/substitution.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <sstream>

using namespace crypto;

std::unordered_set<int> accepted_a = {1,2,5,7,11,13,17,19,23};

bool is_accepted(const int &input) {
    return (accepted_a.end() != std::find(accepted_a.begin(), accepted_a.end(), input));
}

std::string calculate_permutation(const int &a, const int &b) {
    if(!is_accepted(a)) {
        return "";
    }
    std::stringstream ss;
    ss << "[ ";
    for(uint i = 0; i < 27; ++i) {
        char c = static_cast<char>(((a*(i) + b) % 27) + 'a');
        if(c == '{') // apperantly space becomes '{' :)
            c = ' ';
        ss << c << " ";
    }
    ss << "]";
    return ss.str();
}

std::string get_input() {
    std::string line;
    std::getline(std::cin, line);
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
    return line;
}

int main(int argc, char* argv[]) {
    switch(argc) {
        case 4:
            {
                const std::string& arg1(argv[1]);
                int a = atoi(argv[2]);
                int b = atoi(argv[3]);
                Subst_cipher sc;
                if(!sc.set_permutation(calculate_permutation(a, b))) {
                    std::cerr << "Key format not accepted\nexiting..." << std::endl;
                    return -1;
                }
                std::string input = get_input();
                std::string processed;
                if(arg1 == "-d" || arg1 == "-decrypt")
                    processed = sc.decrypt(input);
                else if(arg1 == "-e" || arg1 == "-encrypt") {
                    processed = sc.encrypt(input);
                    std::transform(processed.begin(), processed.end(), processed.begin(), ::toupper);
                    std::cerr << sc.get_permutation() << std::endl;
                }
                std::cout << processed << std::endl;
                break;
            }
        default: 
            {
                // TODO!
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