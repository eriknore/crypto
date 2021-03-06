#ifndef DICT_H
#define DICT_H
#include <fstream>
#include <unordered_set>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

namespace crypto {
    struct Dictionary {
        Dictionary();
        typedef std::unordered_set<std::string> hashmap;
        bool is_a_word(const std::string&) const;
        bool is_english(const std::string&) const;
        hashmap init_from_file(const std::string&);

    private:
        hashmap english;//, swedish;
        //std::vector<hashmap> dictionaries;

    };
}

#endif // DICT_H
