#include <iostream>


class Member {
private:
    int m_value;
public:

    Member(int value) : m_value{value} {
        std::cout << "Member constructed with value " << m_value << std::endl;
    }

};

class Container {
private:
    Member m_member;
public:

    Container(int val)
    {
        std::cout << "Container constructed" << std::endl;

    }
};

int main() {
    // This line will now cause a compile error.
    Container c(42);
    return 0;
}