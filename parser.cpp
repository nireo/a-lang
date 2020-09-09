#include <iostream>
#include <vector>
#include <string>

#include "parser.hpp"

void Parser::assignVariable(const std::vector<std::string>& tokens) {
    if (tokens[1][0] != '=') {
        std::cout
                << "Values need to assigned using the '=' operation. Skipping..."
                << "\n";
        return;
    }

    int variableValue;
    try {
        variableValue = std::stoi(tokens[2]);
    } catch (const std::invalid_argument&) {
        std::cout << "Variable values can only be numbers. Skipping..."
                  << "\n";
        return;
    }

    variables.insert(std::pair<std::string, int>(tokens[0], variableValue));
    std::cout << "Variable " << tokens[0] << " initialized as " << variableValue
              << "!";
}

std::tuple<int, bool> Parser::parseValue(const std::string& stringNumber) {
    int number = 0;
    try {
        number = std::stoi(stringNumber);
        return std::make_tuple(number, true);
    } catch (const std::invalid_argument&) {
        return std::make_tuple(0, false);
    }
}

void Parser::calculate(std::string& input) {
    std::vector<std::string> tokens = tokenizer(input);
    std::vector<int> values;
    std::vector<char> operators;

    for (const auto& token : tokens) {
        std::tuple<int, bool> parsedValue = parseValue(token);
        if (std::get<1>(parsedValue)) {
            values.push_back(std::get<0>(parsedValue));
        } else {
            operators.push_back(token[0]);
        }
    }

    int value = 0;
    for (auto i = 1; i < values.size(); ++i) {
        char o = operators[i - 1];
        if (o == '+')
            value += values[i - 1] + values[i];
        else if (o == '-')
            value += values[i - 1] - values[i];
        else if (o == '*')
            value += values[i - 1] * values[i];
        else if (o == '/')
            value += values[i - 1] / values[i];
        else if (o == '%')
            value += values[i - 1] % values[i];
    }

    std::cout << value << "\n";
}

std::vector<std::string> Parser::tokenizer(std::string& input) {
    std::vector<std::string> tokens;
    std::string delimiter = " ";

    size_t pos = 0;
    std::string token;
    while ((pos = input.find(delimiter)) != std::string::npos) {
        token = input.substr(0, pos);
        tokens.push_back(token);
        input.erase(0, pos + delimiter.length());
    }

    return tokens;
}
