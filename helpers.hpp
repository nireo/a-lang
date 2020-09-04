#ifndef ALANG_ISNUM_HPP
#define ALANG_ISNUM_HPP

#include <array>
#include <string>
bool isNumber(char n);
bool isOperator(char o);
bool isValidNameChar(char c);

std::array<int, 2> parseValue(std::string input, int startIndex);

#endif  // ALANG_ISNUM_HPP
