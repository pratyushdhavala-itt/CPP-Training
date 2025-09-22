#include <iostream>
using namespace std;

int square(int n) {
    return n * n;
}

int main() {
    for (int i = 1; i <= 5; i++) {
        int val = square(i);
        cout << "square(" << i << ") = " << val << endl;
    }
    return 0;
}
