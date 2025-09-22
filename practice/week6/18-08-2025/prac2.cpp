#include <iostream>
using namespace std;

int multiply(int a, int b) {
    int result = a * b;
    return result;
}

int main() {
    int x = 4;
    int y = 7;
    int z = multiply(x, y);
    cout << "Product: " << z << endl;
    return 0;
}
