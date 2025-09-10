#include <iostream>
using namespace std;

class A {

private:
    double a;
public:

};

class B : public A{

private:
    int b;
public:

};

int main() {

    B* b = new B{};

    cout << sizeof(b) << endl;
    
    return 0;
}