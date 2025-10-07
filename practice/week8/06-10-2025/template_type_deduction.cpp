#include <iostream>
using namespace std;

template <typename T>
void refTest(T& x) { cout << typeid(T).name() << endl; }

int main() {
    int a = 5;
    const int b = 10;
    
    refTest(a); 
    refTest(b); 
}
