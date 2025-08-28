#include <iostream>
using namespace std;

int main() {
    
    int a = 5;

    int b = 6;

    char i = 1;
    char c = 0;
    char d = 0;
    char f = 0;

    int* p = (int*) &i;

    void* z = &i;

    cout << z << endl;
    cout << *p << endl;

    cout << &a << endl;
    cout << &b << endl;


    int n = 1;

    char* ptr_n = (char*) &n;

    if (*ptr_n == 1) {
        cout << "TRUE" << endl;
    }
    return 0;
}