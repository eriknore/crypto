#include "substitution.h"

using namespace constants; // alphabet-variables

namespace crypto {
    
    Subst_cipher::Subst_cipher() {
        std::vector<int> list_of_numbers;
        // init list with indexes
        for(uint i = 0; i < size_of_alphabet; ++i) {
            list_of_numbers.push_back(i);
        }

        std::srand(std::time(0)); //use current time as seed for random generator
        // for each number, pick a random number and put in permutation list
        for(uint i = 0; i < size_of_alphabet; ++i) {
                uint random = std::rand() % (list_of_numbers.size());
                permutation.push_back(list_of_numbers[random]);
                list_of_numbers.erase(list_of_numbers.begin()+random);
        }
    }

    Subst_cipher::Subst_cipher(const std::vector<int>& v) : permutation(v) { }

    std::string Subst_cipher::encrypt(const std::string& input) {
        std::stringstream ss;
        for(const char& c : input){
            int letter_nr;
            if(c == ' ')
                letter_nr = size_of_alphabet-1;
            else {
                letter_nr = static_cast<int>(c - 'a');
            }
            if(letter_nr < 0 || letter_nr > 26) // ie. not a-z or space
                continue;
            letter_nr = (letter_nr % size_of_alphabet);
            // example: a->D == 0->3
            // so for a: permutation[0] == 3 and alphabet[3] == d
            ss << alphabet[permutation[letter_nr]];
        }

        return ss.str();
    }

    std::string Subst_cipher::decrypt(const std::string& input) {
        std::stringstream ss;
        for(const char& c : input){
            int letter_nr;
            if(c == ' ')
                letter_nr = size_of_alphabet-1;
            else {
                letter_nr = static_cast<int>(c - 'a');
            }
            if(letter_nr < 0 || letter_nr > 26) // ie. not a-z or space
                continue;
            letter_nr = (letter_nr % size_of_alphabet);
            // find which i where permutation[i] == letter_nr
            for(uint i = 0; i < permutation.size(); ++i) {
                if(permutation[i] == letter_nr) {
                    letter_nr = i;
                    break;
                }
            }
            ss << alphabet[letter_nr];
        }

        return ss.str();
    }

    std::string Subst_cipher::get_permutation() const {
        std::stringstream ss;
        ss << "[ ";
        for(uint i = 0; i < size_of_alphabet; ++i) {
            auto &letter = alphabet[permutation[i]];
            if(letter == ' ')
                ss << "  "; // double space
            else
                ss << static_cast<char>(letter - 32) << " ";
        }
        ss << "]";
        return ss.str();
    }

    bool Subst_cipher::set_permutation(std::string s) {
        if(s.length() != 57)
            return false;
        s = s.substr(2, 53); // removes "[ " and " ]"
        for(uint i = 0; i < s.length(); ++i) {
            if(i % 2 == 1) // i.e. is whitespace
                continue;
            if(s[i] == ' ')
                permutation[i/2] = size_of_alphabet-1;
            else
                permutation[i/2] = static_cast<int>(s[i] - 'a');
                
        }
        return true;
    }
}