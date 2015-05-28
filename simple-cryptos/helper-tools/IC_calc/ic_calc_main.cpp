#include <istream>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include "ic_calc.h"

using namespace crypto;

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
    IC_calc ic;
    std::cout << "IC_calc = " << ic.calculate(input) << std::endl;


    return 0;
}