#include <iostream>
using namespace std;

int main() {
    
    int a = 10;
    int b = 20;
    int& num = a;
    int& num2 = num;

    int* p;
    {
        int c = 10;
        p = &c;
        cout << *p << endl;
        cout << &c << endl;
    }

    int d = 20;
    cout << &d << endl;

    cout << *p << endl;

    int e = 30;

    return 0;
}