#include <iostream>
using namespace std;

template <typename T>
class Printer {
public:
    void print(T value) {
        cout << "Generic: " << value << endl;
    }
};

template<>
class Printer<bool> {
public:
    void print(bool value) {
        std::cout << (value ? "true" : "false") << '\n';
    }
};


int main() {
    Printer<int> p1;
    p1.print(100);

    Printer<bool> p2;
    p2.print(true);
}
