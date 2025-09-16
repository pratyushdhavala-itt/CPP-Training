#include <iostream>
using namespace std;

class Counter {
public:
    int value{};
    Counter(int v = 0) : value(v) {}

    Counter operator+=(const Counter& rhs) {
        value += rhs.value;
        return *this;
    }
};

int main() {
    Counter x(1), y(2), z(3);
    x += y += z; 

    cout << "x: " << x.value << ", y: " << y.value << '\n';
    return 0;
}
