#include <iostream>
using namespace std;

int add(int a, int b) {
    return a + b;
}

int main() {
    
    int x = 7;
    int y = 1;
    int z = add(x, y);
    x = add(z, x);

    
    return 0;
}