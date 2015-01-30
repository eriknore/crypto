#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    std::string arg1;
    switch(argc) {
        case 2: 
            {   
                // Caesar cipher is shift cipher with K = 3
                arg1 = std::string(argv[1]);
                if(arg1 == "-e" || arg1 == "-encrypt") {
                    system("./shift_cipher -e 3");
                    break;
                } else if(arg1 == "-d" || arg1 == "-decrypt"){
                    system("./shift_cipher -d 3");
                    break;
                }
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

    return 0;
}