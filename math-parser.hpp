//
// Created by eemil on 11/1/20.
//

#ifndef ALANG_MATH_PARSER_HPP
#define ALANG_MATH_PARSER_HPP

#include <vector>
#include <string>

class MathParser {
public:
    double CalculatePostfix();
    void InfixToPostfix(const std::string& infix);
private:
    std::string postfix;
};

#endif //ALANG_MATH_PARSER_HPP
