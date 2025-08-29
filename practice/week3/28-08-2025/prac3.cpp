#include <iostream>
using namespace std;

int main() {
    
    int* arr = new int[5]{};

    *arr = 1;
    *(arr + 1) = 2;
    *(arr + 2) = 3;
    *(arr + 3) = 4;
    *(arr + 4) = 5;

    cout << *arr << endl;
    cout << *(arr + 1) << endl;
    cout << arr << endl;
    cout << arr + 1 << endl;


    delete[] arr;

    // arr = arr + 1;
    // delete (arr);
    
    //delete (arr);

    //cout << *arr << endl;
    cout << (arr + 1) << endl;
    cout << *(arr + 2) << endl;
    return 0;
}