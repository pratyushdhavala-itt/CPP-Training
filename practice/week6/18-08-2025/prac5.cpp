#include <iostream>
using namespace std;

void level3(int* p) {
    *p = 42;
}

void level2(int* p) {
    cout << "In level2" << endl;
    level3(p);
}

void level1() {
    cout << "In level1" << endl;
    int* ptr = nullptr; 
    level2(ptr);
}

int main() {
    cout << "Starting program..." << endl;
    level1();
    cout << "Program finished" << endl;
    return 0;
}
