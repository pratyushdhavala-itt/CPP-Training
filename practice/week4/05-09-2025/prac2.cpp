#include <iostream>
using namespace std;

int add(int a, int b) {
    return a + b;
}

int main() {
    
    const int a = 5;
    const int b = 10;
    cout << add(a, b) << endl;
    return 0;
}