#include <istream>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>


// line by line:
void read_line(std::istream& is, std::stringstream& dest) {
    std::string line;
    std::getline(is, line);
    dest << line;
}

// line by line:
void read_lines(std::istream& is, std::stringstream& dest) {
    std::string line;
    // store the line to the output iterator
    while (std::getline(is, line))
        dest << line;
}

int main() {
    std::stringstream ss;
    // read_lines(std::cin, ss);
    read_line(std::cin, ss);
    std::string input = ss.str();
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
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
    std::cout << "IC = " << ic << "   nr of chars = " << tot_count << std::endl;

    return 0;
}