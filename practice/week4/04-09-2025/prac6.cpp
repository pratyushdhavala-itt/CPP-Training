#include <iostream>

class Something {
public:
    int m_x{};
    Something(int x) : m_x{x} { std::cout << "Normal constructor\n"; }
    Something(const Something& s) : m_x{s.m_x} { std::cout << "Copy constructor\n"; }
    void print() const { std::cout << "Something(" << m_x << ")\n"; }
};

int main() {
    Something s { Something { 5 } };
    s.print();
}
