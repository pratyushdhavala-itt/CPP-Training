#include <iostream>
using namespace std;

int main() {
    
    int (*a)[4] = new int[5][4];

    cout << a << endl;
    cout << &a[0] << endl;
    cout << a[0] << endl;
    cout << &a[0][4] << endl;
    cout << &a[1][0] << endl;

    // for (int i = 0; i < 5; i++) {

    // }

    // int b = 5;
    // int* ptr_b = &b;

    // delete &b;
    return 0;
}