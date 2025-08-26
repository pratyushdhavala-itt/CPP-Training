#include <iostream>
using namespace std;

int z = 40;

int main() {
    
    int* ptr_z = &z;
    cout << ptr_z << endl;
    int a = 5;
    
    int* ptr_a = &a;

    cout << ptr_a << endl;

    int b = 20;

    int* ptr_b = &b;

    cout << ptr_b << endl;

    int* ptr_c;
    {
        int c = 35;
        ptr_c = &c;
        cout << ptr_c << endl;
        //cout << *ptr_c << endl;
    }

    //cout << *ptr_c << endl;

    int d = 40;
    int* ptr_d = &d;

    cout << ptr_d << endl;

    cout << *ptr_c << endl;

    cout << boolalpha << (ptr_c == ptr_d) << endl;
}