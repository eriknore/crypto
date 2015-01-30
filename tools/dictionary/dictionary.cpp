#include "dictionary.h"

#include <iostream>

namespace crypto {
    Dictionary::Dictionary() {
        //swedish = init_from_file("resources/wordlists/svenska.txt");
        english = init_from_file("tools/dictionary/wordlists/english.txt");
        
        //dictionaries.push_back(swedish);
        //dictionaries.push_back(english);
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
        if(english.end() != std::find(english.begin(), english.end(), candidate))
            return true;
        return false;
    }

    bool Dictionary::is_english(const std::string& candidate) const {
        // split string on whitespace
        std::vector<std::string> words;
        std::stringstream ss(candidate);
        std::string item;
        while (std::getline(ss, item, ' ')) {
            words.push_back(item);
        }

        // count nr of recognized words
        uint nr_of_words_found = 0;
        uint size = words.size();
        for(uint i = 0; i < size; ++i) {
            if(is_a_word(words[i]))
                ++nr_of_words_found;
        }
        
        // is english iff more than 30% of the words were recognized
        // might need trimmin?
        if((float(nr_of_words_found) / size) > 0.3) 
            return true;
        else
            return false;
    }
}