#include <iostream>
using namespace std;


class Box {
public:
    int value{};
    Box(int v = 0) : value(v) {
        cout << "called" << endl;
    }

    Box& operator=(const Box& rhs) {
        value = rhs.value;
        return *this;
    }

    Box(const Box& b) {
        cout << "called copy:" << endl;
    }
};

int main() {
    Box a, b, c(42);
    cout << "start: " << endl;
    a = b = c; 

    cout << "a: " << a.value << ", b: " << b.value << '\n';
    return 0;
}
