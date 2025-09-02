#include <iostream>
using namespace std;

const int& setValue(int x) {
    int y = x;
    return 10;
}

int main() {
    
    //int b = 4;
    const int& a = setValue(5);

    //cout << setValue(5) << endl;

    cout << a << endl;
    return 0;
}