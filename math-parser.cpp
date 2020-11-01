#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <cmath>
#include "math-parser.hpp"

void MathParser::InfixToPostfix(const std::string& infix) {
    const std::string ops = "-+/*^";
    std::stringstream ss;
    std::stack<int> s;

    std::stringstream input(infix);
    std::string token;
    while (std::getline(input, token, ' ')) {
        if (token.empty()) {
            continue;
        }

        char c = token[0];
        size_t idx = ops.find(c);

        if (idx != std::string::npos) {
            while (!s.empty()) {
                int prec2 = s.top() / 2;
                int prec1 = idx / 2;
                if (prec2 > prec1 || (prec2 == prec1 && c != '^')) {
                    ss << ops[s.top()] << ' ';
                    s.pop();
                } else break;
            }
            s.push(idx);
        } else if (c == '(') {
            s.push(-2);
        } else if (c == ')') {
            while (s.top() != -2) {
                ss << ops[s.top()] << ' ';
                s.pop();
            }
            s.pop();
        } else {
            ss << token << ' ';
        }
    }

    while (!s.empty()) {
        ss << ops[s.top()] << ' ';
        s.pop();
    }

    postfix = ss.str();
}

double MathParser::CalculatePostfix() {
    std::istringstream iss(postfix);
    std::vector<double> stack;
    std::string token;

    while (iss >> token) {
        double tokenN;
        if (std::istringstream(token) >> tokenN)
            stack.push_back(tokenN);
        else {
            double secondOperand = stack.back();
            stack.pop_back();
            double firstOperand = stack.back();
            stack.pop_back();
            if (token == "*")
                stack.push_back(firstOperand * secondOperand);
            else if (token == "/")
                stack.push_back(firstOperand / secondOperand);
            else if (token == "-")
                stack.push_back(firstOperand - secondOperand);
            else if (token == "+")
                stack.push_back(firstOperand + secondOperand);
            else if (token == "^")
                stack.push_back(std::pow(firstOperand, secondOperand));
            else {
                std::cerr << "Error" << std::endl;
                std::exit(1);
            }
        }
        std::cout << std::endl;
    }

    return stack.back();
}

int main() {
    std::string infix = "3 + 5 + ( 2 * 3 )";
    MathParser mp;
    mp.InfixToPostfix(infix);

    std::cout << mp.CalculatePostfix() << "\n";
}