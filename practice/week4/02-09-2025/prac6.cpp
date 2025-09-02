#include <iostream>
using namespace std;

int main() {
    
    int* ptr_a = (int*) malloc(4);
    *ptr_a = 3;
    // free(ptr_a);
   // ptr_a = (int*) realloc(ptr_a, 1);
    delete ptr_a;
    cout << ptr_a << endl;

    int* ptr_b = new int(44);
    cout << *ptr_b << endl;
    free(ptr_b);
    cout << ptr_b << endl;

    int* ptr_c = new double(50);
    return 0;
}