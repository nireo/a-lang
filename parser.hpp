#ifndef ALANG_PARSER_HPP
#define ALANG_PARSER_HPP

#include <vector>
#include <string>
#include <map>

class Parser {
public:
    void assignVariable(const std::vector<std::string>& tokens);

    static void calculate(std::string& input);
    static std::tuple<int, bool> parseValue(const std::string& stringNumber);
    static std::vector<std::string> tokenizer(std::string& input);

private:
    std::map<std::string, int> variables;
};


#endif //ALANG_PARSER_HPP
