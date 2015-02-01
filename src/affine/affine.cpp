#include "affine.h"

namespace crypto {

    const std::unordered_set<int> Affine_cipher::accepted_a = {1,2,5,7,11,13,17,19,23};
    
    bool Affine_cipher::a_is_accepted(const int &input) {
        return (accepted_a.end() != std::find(accepted_a.begin(), accepted_a.end(), input));
    }
    
    void Affine_cipher::set_permutation(const int &a, const int &b) {
        std::stringstream ss;
        ss << "[ ";
        for(uint i = 0; i < 27; ++i) {
            char c = static_cast<char>(((a*(i) + b) % 27) + 'a');
            if(c == '{') // apperantly space becomes '{' :)
                c = ' ';
            ss << c << " ";
        }
        ss << "]";
        Subst_cipher::set_permutation(ss.str());
    }

    std::string Affine_cipher::encrypt(const std::string &input, const int &a, const int &b) {
        if(!a_is_accepted(a))
            return "Input 'a' must be a multiplicative inverse of the size of alphabet\nexiting...";
        set_permutation(a, b);
        return Subst_cipher::encrypt(input);
    }
    
    std::string Affine_cipher::decrypt(const std::string &input, const int& a, const int& b) {
        if(!a_is_accepted(a))
            return "Input 'a' must be a multiplicative inverse of the size of alphabet\nexiting...";
        set_permutation(a, b);
        return Subst_cipher::decrypt(input);
    }

}