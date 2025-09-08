#include <iostream>
using namespace std;

class A {

private:

    int x;
    int y = x;

public:
    A(int x) : x(x) {

    }

    int getY() {
        return y;
    }
};

int main() {
    
    A a(4);
    cout << a.getY() << endl;
    return 0;
}