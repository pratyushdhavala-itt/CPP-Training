#include <iostream>
using namespace std;

class Test;
void outInc(const Test& t);
class Test {
public:
    int x;
    int y;

public:
    void increment() const {
        cout << "increment called" << endl;
        outInc(*this);  // pass const Test by value, makes a copy
    }
};

void outInc(const Test& t) {
    //t.x++;
    cout << "Inside outInc, x = " << t.x << endl;
}

int main() {
    Test t1{1, 2};
    t1.increment();
    return 0;
}
