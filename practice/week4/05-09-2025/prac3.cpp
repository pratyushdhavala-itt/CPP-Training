#include <iostream>
using namespace std;

class A {
public:
    int x = 5;
};

void increment(const A& a) {
    a.x++;
}

int main() {
    const A a;
    increment(a);
    cout << a.x << endl;
    return 0;
}