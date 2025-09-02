#include <iostream>
using namespace std;

int main() {
    
    // int* a = (int*) calloc (100000000000, 10000000000);
    // int* b = (int*) malloc (100000000000 * 10000000000);

    const char* c = (const char*) calloc(10, 1);
    c = "hellohihihiihihihihihihih";


    cout << c << endl;

    int* ptr = new int(4);
    ptr = (int*) new double(5.4);
    return 0;
}