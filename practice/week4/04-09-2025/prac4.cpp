#include <iostream>
#include <string>

class Test {
private:
    int m_x;
    int m_y;

public:

    Test(int x)
        :  m_x{42}, Test(x, 0) 
    {
    }

    Test(int x, int y)
        : m_x{x}, m_y{y}
    {
        std::cout << "Test(" << m_x << ", " << m_y << ")\n";
    }
};