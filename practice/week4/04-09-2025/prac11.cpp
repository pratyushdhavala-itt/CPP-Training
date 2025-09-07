#include <iostream>
using namespace std;

class Animal {

public:

    int a;

    Animal() {
        cout << "constructor called" << endl;
    }

    Animal(int a) {
        cout << this->a << "constructor called" << endl;
    }
    
    ~Animal() {
        cout << "destructor called" << endl;
    }
};

int main() {
    
    Animal abc;

    return 0;
}