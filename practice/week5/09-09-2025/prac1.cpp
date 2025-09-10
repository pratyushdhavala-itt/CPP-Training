#include <iostream>
using namespace std;

class Base {

private:

    const int x = 5;
    const int y = 3234;

public:

    Base() : x(10), y(20) {
        // cout << x << endl;
        // cout << y << endl;
        cout << "base constructor called" << endl;
    }

    Base(Base& b) {
        cout << "base copy constructor called" << endl;
    }

    int getX() {
        return x;
    }
};

class Derived : public Base {

private:

    int a;
    int b;

public:

    Derived(int a, int b) : a{a}, b{b} {
        cout << "derived constructor called" << endl;
    }
    Derived(Derived& d) {
        cout << "derived copy constructor called" << endl;
        a = d.a;
        b = d.b;
    }
    Derived& operator=(const Derived& d) {
        cout << "derived copy assignment operator called" << endl;
        a = d.a;
        b = d.b;
        return *this;
    }

    int getA() {
        return a;
    }
    int getB() {
        return b;
    }

};

int main() {
    
    // Derived d1;
    // //cout << d.getInt() << endl;
    // Derived d2 = d1;
    // Derived d3(d2);
    // d1 = d3;

    Derived d1(1, 2);
    Derived d2(3, 4);
    Derived d3(d2);
    d3 = d1;

    cout << d3.getA() << endl;
    return 0;
}