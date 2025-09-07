#include <iostream>

class IntPair {
private:
    int m_x{}, m_y{};
public:
    IntPair(int x, int y) : m_x{x}, m_y{y} {}

    int x() const { return m_x; }
    int y() const { return m_y; }
};

void print(IntPair p) {
    std::cout << "(" << p.x() << ", " << p.y() << ")\n";
}

IntPair ret3() {

    return {7, 8};
}

int main() {
    print(IntPair{5, 6}); 
    print({7, 8});        
    print(ret3());        
    return 0;
}
