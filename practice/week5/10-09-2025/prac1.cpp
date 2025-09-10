#include <iostream>
using namespace std;

class Base {

private:

public:

    void print() {
        cout << "BASE CLASS" << endl;
    }

};

class Derived : public Base {

private:

public:

    void print() {
        cout << "DERIVED CLASS" << endl;
    }


};


int main() {
    
    Derived d;
    Base b;

    b.print();
    
    return 0;
}