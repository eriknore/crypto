#include "../helper-tools/IC_calc/ic_calc.h"
#include "../src/vigenere/vigenere.h"
#include "../src/constants.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace crypto;
using namespace constants;

int find_block_size(const std::string &input) {
    IC_calc ic;
    // if key consists of more than 30 chars then this will fail!
    for(uint i = 2; i < 30; ++i) {
        uint nr_of_blocks = 1 + input.length() / i;
        double ic_s = 0;
        for(uint j = 0; j < nr_of_blocks; ++j) {
            //std::cerr << input.substr(j, i) << std::endl;
            ic_s += ic.calculate(input.substr(j, i));
        }
        std::cout << ic_s << " " << nr_of_blocks << std::endl;
        std::cout << "For m = " << i << ", IC = " << ic_s/nr_of_blocks << std::endl;
    }
    return -1;
}

std::string get_input() {
    std::string line;
    std::getline(std::cin, line);
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
    return line;
}

int main(int argc, char* argv[]) {
    std::cout << "Input cipher:\n";
    std::string input = get_input();
    int m = find_block_size(input);

    return 0;
}