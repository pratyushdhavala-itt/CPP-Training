#include <iostream>
using namespace std;

class Counter {
public:
    int value{};
    Counter(int v = 0) : value(v) {}

    Counter operator++() {
        ++value;
        return *this;
    }
};

int main() {
    Counter c(5);
    ++(++c);
    cout << c.value << '\n';
    return 0;
}
