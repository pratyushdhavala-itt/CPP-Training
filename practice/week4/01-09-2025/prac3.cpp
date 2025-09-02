#include <iostream>
using namespace std;

int& add(int& result, int a, int b) {
    result = a + b;
    return result;
}

int (&returnArr(int (&arr)[5]))[5] {
    return arr;
}

int main() {
    
    // int a = 5;
    // int b = 6;

    // int result = add(result, a, b);

    // cout << result << endl;

    // int arr[] = {1,2,3,4,5};
    // cout << returnArr(arr) << endl;

//     int* p = new int(42);
// int& ref = *p;
// delete p;
// cout << ref;  

while (true) {
    int* ptr = new int(50); // Killed
}


    return 0;
}