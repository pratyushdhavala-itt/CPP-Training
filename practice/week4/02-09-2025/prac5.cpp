#include <iostream>
using namespace std;

int main() {
    
    int* ptr = new int(5);
    cout << ptr << endl;
    *ptr = (*ptr) * (*ptr);

    // void* ptr_v = ptr;
    // cout << *ptr_v << endl;

    // int i = 1;
    // int j = 2;
    // int& f = i + j;

    // &i = 4;
    int n = NULL;
    cout << n << endl;
    return 0;
}