#include <ciso646>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using std::string;
using std::vector;

// extend the vector class
template<typename T>
struct stack : public std::vector<T> {
    using base_type = std::vector<T>;

    // push item to the vector, but also return that same value
    T push(const T &x) {
        base_type::push_back(x);
        return x;
    }

    // get the last element
    const T &top() { return base_type::back(); }
    
    T pop() {
        T x = std::move(top());
        base_type::pop_back();
        return x;
    }

    // empty the whole vector
    bool empty() { return base_type::empty(); }
};

// enum to describe operator position
enum class Associates {
    none, left_to_right, right_to_left
};

struct Operator {
    int precedence;
    Associates associativity;
};

std::unordered_map<string, Operator> Operators = {
        // operator name, priority, and position
        {"^", {4, Associates::right_to_left}},
        {"*", {3, Associates::left_to_right}},
        {"/", {3, Associates::left_to_right}},
        {"+", {2, Associates::left_to_right}},
        {"-", {2, Associates::left_to_right}},
};

// get operator priority
int precedence(const string &op) { return Operators[op].precedence; }

// get associates
Associates associativity(const string &op) {
    return Operators[op].associativity;
}

// helper functions
bool is_number(const string &t) {
    return regex_match(t,
                       std::regex{R"z((\d+(\.\d*)?|\.\d+)([Ee][\+\-]?\d+)?)z"});
}

bool is_operator(const string &t) { return Operators.count(t); }

bool is_open_parenthesis(const string &t) { return t == "("; }

bool is_close_parenthesis(const string &t) { return t == ")"; }

bool is_parenthesis(const string &t) {
    return is_open_parenthesis(t) or is_close_parenthesis(t);
}

template<typename T>
std::ostream &operator<<(std::ostream &outs, const std::vector<T> &xs) {
    std::size_t n = 0;
    for (auto x : xs) outs << (n++ ? " " : "") << x;
    return outs;
}

vector<string> parse(const vector<string> &tokens) {
    vector<string> output;
    stack<string> stack;

    // loop over the tokens
    for (auto token : tokens) {
        if (is_number(token))
            // push numbers to front of the output
            output.push_back(token);

            // handle operators and parenthesies
        else if (is_operator(token) or is_parenthesis(token)) {
            if (!is_open_parenthesis(token)) {
                while (!stack.empty() and
                       ((is_close_parenthesis(token) and
                         !is_open_parenthesis(stack.top())) or
                        (precedence(stack.top()) > precedence(token)) or
                        ((precedence(stack.top()) == precedence(token)) and
                         (associativity(token) == Associates::left_to_right))))
                    output.push_back(stack.pop());

                if (is_close_parenthesis(token)) stack.pop();
            }
            if (!is_close_parenthesis(token)) stack.push(token);
        } else
            throw;
    }

    while (!stack.empty()) output.push_back(stack.pop());
    return output;
}

int main(int argc, char **argv) {
    auto tokens = vector<string>(argv + 1, argv + argc);
    auto rpn_expr = parse(tokens);

    std::cout << "\nInfix = " << tokens << "\nRPN   = " << rpn_expr << "\n";
}
