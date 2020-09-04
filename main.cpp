#include <ctype.h>

#include <array>
#include <iostream>
#include <map>
#include <vector>

#include "helpers.hpp"

int main() {
    std::string input;
    std::map<std::string, int> variables;

    for (;;) {
        std::cin >> input;
        if (input == ".exit") {
            break;
        } else {
            std::vector<int> values;
            std::vector<char> operators;
            for (auto i = 0; i < input.size(); i++) {
                if (isNumber(input[i])) {
                    std::array<int, 2> valueAndIndex = parseValue(input, i);
                    i = valueAndIndex[1];

                    values.push_back(valueAndIndex[0]);
                } else if (isOperator(input[i])) {
                    operators.push_back(input[i]);
                } else if (input[i] == ' ') {
                    continue;
                } else {
                    // TODO: lisää muuttijat
                    std::string name = "";
                    int j;
                    for (j = i; isValidNameChar(input[j]); j++) {
                        name.push_back(input[j]);
                    }
                }
            }

            int value = 0;
            for (auto i = 1; i < values.size(); ++i) {
                char o = operators[i - 1];
                if (o == '+') {
                    value += values[i - 1] + values[i];
                } else if (o == '-') {
                    value += values[i - 1] - values[i];
                } else if (o == '*') {
                    value += values[i - 1] * values[i];
                } else if (o == '/') {
                    value += values[i - 1] / values[i];
                } else if (o == '%') {
                    value += values[i - 1] % values[i];
                }
            }
            std::cout << value << "\n";
        }
    }
}
