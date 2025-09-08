#include <iostream>

class Calculator {
private:
    int m_value { 0 };

public:
    Calculator& add(int value) { m_value += value; return *this;}
    Calculator& subtract(int value) { m_value -= value; return *this;}
    Calculator& multiply(int value) { m_value *= value; return *this;}

    int getValue() const { return m_value; }
};

int main() {
    Calculator calc;
    calc.add(5).subtract(2).multiply(4);

    std::cout << calc.getValue() << std::endl;
    return 0;
}