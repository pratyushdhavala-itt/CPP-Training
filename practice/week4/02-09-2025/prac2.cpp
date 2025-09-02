#include <iostream>
using namespace std;

// int* badFunc() {
//     int x = 10;     // local on stack
//     return &x;      // ❌ pointer to destroyed object
// }
#include <iostream>
int main() {
    double d = 3.14;
    char* p = (char*) (&d);
    int* q = reinterpret_cast<int*>(p + 1); // ❌ misaligned
    std::cout << *q << std::endl; // UB on most systems
}
