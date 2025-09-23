#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdexcept>
#include <string>

class Calculator {
public:
    int add(int a, int b) { return a + b; }
    int sub(int a, int b) { return a - b; }
    int mul(int a, int b) { return a * b; }
    int divi(int a, int b) {
        if (b == 0) throw std::invalid_argument("division by zero");
        return a / b;
    }
    std::string repeat(char c, int n) {
        return std::string(n, c);
    }
};

#endif 
