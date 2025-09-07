#include <iostream>
using namespace std;

class Foo {

    const int m_x;
public:
    // Foo(int x) : m_x {x} {
    //     cout << m_x << endl;
    // }

    // Foo() = default;
};

int main() {

    Foo{};
}