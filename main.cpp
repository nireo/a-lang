#include <iostream>
#include <map>
#include <vector>
#include "helpers.hpp"

struct Token {
    std::string value;
    std::string key;
};

class Parser {
public:

};

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
                    int value = 0;
                    int j;
                    for (j = i; isNumber(input[j]); j++) {
                        value *= 10;
                        value += input[j] - '0';
                    }

                    i = j - 1;
                    values.push_back(value);
                } else if (isOperator(input[i])) {
                    operators.push_back(input[i]);
                } else {
                    continue;
                }
            }

            int value = 0;
            for (auto i = 1; i < values.size(); ++i) {
                char o = operators[i - 1];
                if (o == '+') {
                    value += values[i - 1] + values[i];
                } else if (o == '-') {
                    value -= values[i - 1] - values[i];
                } else if (o == '*') {
                    if (value == 0)
                        value = 1;
                    value *= values[i - 1] * values[i];
                } else if (o == '/') {
                    if (value == 0)
                        value = 1;
                    value += values[i - 1] / values[i];
                } else if (o == '%') {
                    value += values[i - 1] % values[i];
                }
            }

            std::cout << value << "\n";
        }
    }
}
