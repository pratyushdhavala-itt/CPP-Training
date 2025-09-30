#include <iostream>
using namespace std;

template <class T, class U>
auto add(T x, U y) {

    cout << "First one called" << endl;
    return x + y;
}

int add(int x, int y) {

    cout << "Second one called" << endl;
    return x + y;
}

const char* add(const char* x, const char* y) = delete;

int main() {

    auto a = add(5, 5.5);
    cout << a << endl;
    cout << "Type: " << typeid(a).name() << endl;
    return 0;
}

