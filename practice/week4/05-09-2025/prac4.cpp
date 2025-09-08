#include <iostream>
using namespace std;

class A {
private:
    int x = 8;

public:
    int& getX() {
        return x;
    }
};

int main() {
    
    A a;
    a.getX() = 99;
    cout << a.getX() << endl;

    return 0;
}