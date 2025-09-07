#include <iostream>
using namespace std;

class Foo {
public:
    int x;
    Foo() { // default constructor
        std::cout << "Foo default constructed\n";
    }
};

int main() {
    Foo foo(); // Calls default constructor

    cout << foo.x;
    return 0;
}
