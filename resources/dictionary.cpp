#include "dictionary.h"

#include <iostream>

namespace crypto {
    Dictionary::Dictionary() {
        swedish = init_from_file("resources/wordlists/svenska.txt");
        english = init_from_file("resources/wordlists/english.txt");
        
        dictionaries.push_back(swedish);
        dictionaries.push_back(english);
    }

    Dictionary::hashmap Dictionary::init_from_file(const std::string& file) {
        Dictionary::hashmap set;
        std::ifstream infile(file);
        std::string line;
        while (std::getline(infile, line))
            set.insert(line);

        return set;
    }

    bool Dictionary::is_a_word(const std::string& candidate) const {
        for(uint i = 0; i < dictionaries.size(); ++i) {
            const hashmap& d = dictionaries[i];
            if(d.end() != std::find(d.begin(), d.end(), candidate))
                return true;
        }
        
        return false;
    }
}