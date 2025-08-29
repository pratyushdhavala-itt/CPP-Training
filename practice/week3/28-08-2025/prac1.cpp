#include <iostream>
using namespace std;

// 12.12 return by reference and return by address

const int& returnReference(int& c) {

    static int a = 5; // must be static, else segmentation fault will occur
    cout << &c << endl;
    return c;
}

const int& returnLiteralReference() {

    return 9;
}

const int& returnByConstReference(const int& ref) {

    return ref;
}

const int& tryAgain() {
    int a = 19;
    return 16;
}

const string& foo(const string& s) {
    return s;
}

int main() {
    int c = 7;
    cout << &c << endl;
    const int& b = returnReference(c);
    cout << b << endl;
    cout << &returnReference(c) << endl;

    const int& d = 6;
    cout << &d << endl;

    //cout << returnLiteralReference() << endl;

    const int& e {returnByConstReference(6)};
    const int& f = returnByConstReference(8);

    cout << e << endl;

    // int g = returnLiteralReference();
    // cout << g << endl;

    int* ptr = NULL;

    cout << ptr << endl;

    return 0;
}