#include <iostream>
using namespace std;

int c = 5;

int main() {
    
    // int n = 5;
    // int arr[n];

    int* a = new int (5);
    int b = 5;

    cout << a << endl;
    cout << &b << endl;
    cout << &c << endl;

    int* d = new int (10);

    cout << d << endl;
    
    int* e = a;

    cout << *e << endl;

    delete a;

    cout << *e << endl;

    short* f = (short*) new int(5);

    cout << *f << endl;

    return 0;
}