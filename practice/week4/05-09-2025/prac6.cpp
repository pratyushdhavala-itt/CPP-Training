#include <iostream>
using namespace std;

class A {

    int x;
    int y;

public:
    
    A(A a) {};
    A(int x) {
        x = x;
    };
};

int main() {
    
    //A a;
    return 0;
}