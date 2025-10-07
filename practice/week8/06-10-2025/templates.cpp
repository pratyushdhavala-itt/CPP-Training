#include <iostream>
using namespace std;

template <typename T>
T mmax(T a, T b) {
    return (a > b) ? a : b;
}

template <typename T1, typename T2>
void printPair(T1 a, T2 b) {
    cout << a << " and " << b << endl;
}

int main() {

    cout << mmax(3, 7) << endl;          
    cout << mmax<int>(3.5, 2.1) << endl;     
    cout << mmax("abc"s, "xyz"s) << endl;

    printPair(3, 4.5);        // T1 = int, T2 = double
    printPair("Hello", 42); 
    
    return 0;
}

