#include <iostream>
using namespace std;

class A {


private:
    int* data;

public:
    A(int x) {
        data = new int;
        *data = x;
    }

    A(A &a) {
        data = a.data;
    }

    void increment() {
        (*data)++;
    }

    int returnX() {
        return *data;
    }

    
};

int main() {
    
    A a1(5);

    A a2(a1);

    a1.increment();

    cout << a1.returnX() << endl;
    cout << a2.returnX() << endl;

    a2.increment();

    cout << a1.returnX() << endl;
    cout << a2.returnX() << endl;
    
    return 0;
}
