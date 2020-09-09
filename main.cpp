#include <iostream>
#include <string>

#include "parser.hpp"

int main() {
    std::string input;
    for (;;) {
        std::getline(std::cin, input);
        if (input == ".exit") {
            break;
        } else {
            input += " t";
            Parser::calculate(input);
        }
    }
}
