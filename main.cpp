#include <array>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>

#include "helpers.hpp"


// mahdollinen parser class tulevaisuutta varten
class Parser {
public:
    void assignVariable(const std::vector<std::string>& tokens);
    static std::vector<std::string> tokenizer(const std::string& input, char deliminator);
private:
    std::map<std::string, int> variables;
};

void Parser::assignVariable(const std::vector<std::string> &tokens) {
    if (tokens[1][0] != '=') {
        std::cout << "Values need to assigned using the '=' operation. Skipping..." << "\n";
        return;
    }

    int variableValue;
    try {
        variableValue = std::stoi(tokens[2]);
    } catch (const std::invalid_argument&) {
        std::cout << "Variable values can only be numbers. Skipping..." << "\n";
        return;
    }

    variables.insert(std::pair<std::string, int>(tokens[0], variableValue));
    std::cout << "Variable " << tokens[0] << " initialized as " << variableValue << "!";
}

std::vector<std::string> Parser::tokenizer(const std::string &input, char deliminator) {
    std::vector<std::string> tokens;
    std::stringstream s_stream(input);
    std::string temp;

    while( getline(s_stream, temp, deliminator)) {
        tokens.push_back(temp);
    }

    return tokens;
}

int main() {
    std::string input;
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
