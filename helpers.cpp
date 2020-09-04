#include <array>
#include <string>

bool isNumber(char n) {
    switch (n) {
        case '1':
            return true;
        case '2':
            return true;
        case '3':
            return true;
        case '4':
            return true;
        case '5':
            return true;
        case '6':
            return true;
        case '7':
            return true;
        case '8':
            return true;
        case '9':
            return true;
        default:
            return false;
    };
}

bool isOperator(char o) {
    switch (o) {
        case '+':
            return true;
        case '-':
            return true;
        case '*':
            return true;
        case '/':
            return true;
        case '%':
            return true;
        default:
            return false;
    };
}

// tarkaste siististi kelpaako char nimeen
bool isValidNameChar(char c) {
    if (isNumber(c)) return false;
    if (isOperator(c)) return false;
    if (c == ' ') return false;

    return true;
}

// palauta arvo ja viimeinen indeksi. [0] = arvo, [1] = index
std::array<int, 2> parseValue(std::string input, int startIndex) {
    int value = 0, i;
    for (i = startIndex; isNumber(input[i]); i++) {
        value *= 10;
        value += input[i] - '0';
    }

    return {value, i - 1};
}
