#include <iostream>
using namespace std;

int& getNum() {

    int a = 4;
    return a;
}

int& getInt() {
    static int a = 5;
    return a;
}
int main() {
    
    int a = getInt();
    cout << a << endl;

    int* z = new int(543);
    delete z;
    cout << *z << endl;
    return 0;
}