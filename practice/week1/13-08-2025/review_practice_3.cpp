#include <iostream>
using namespace std;


void byValue(int x) {
    cout << "[byValue] Received: " << x << endl;
    x += 10; 
    cout << "[byValue] Modified local copy: " << x << endl;
}

//int& x;
void byReference(int& x) {
    cout << "[byReference] Received: " << x << endl;
    x += 10; 
    cout << "[byReference] Modified original: " << x << endl;
}


void byConstReference(const int& x) {
    cout << "[byConstReference] Received: " << x << endl;

}


void byPointer(int* x) {
    if (x) { 
        cout << "[byPointer] Received: " << *x << endl;
        *x += 10; 
        cout << "[byPointer] Modified original: " << *x << endl;
    } else {
        cout << "[byPointer] Received null pointer" << endl;
    }
}

void passingPointer(int *y) {
    *y += 5;
}

void normal(int y) {
    y += 5;
}

void sample(int (&arr)[5]) {

    for (int i : arr) {
        cout << i << " ";
    }

    cout << size(arr) << endl;
}

void sample_one(int (*arr)[5]) {
    for (int i : *arr) {
        cout << i << " ";
    }
    cout << typeid(arr[0]).name() << endl;

    cout << arr[0] << endl;
}
int main() {
    int num = 5;

    cout << "\nInitial value: " << num << "\n";

    byValue(num);           // copy
    cout << "After byValue: " << num << "\n\n";

    byReference(num);       // reference
    cout << "After byReference: " << num << "\n\n";

    byConstReference(num);  // const reference
    cout << "After byConstReference: " << num << "\n\n";

    byPointer(&num);        // pointer
    cout << "After byPointer: " << num << "\n\n";

    byPointer(nullptr);     // pointer to nothing

    int y = 10;
    normal(y);
    cout << y << endl;
    passingPointer(&y);
    cout << y << endl;

    int a[] = {1, 2, 3, 4, 5};
    sample(a);
    sample_one(&a);

    int z = 1;
    int &r = z;

    cout << &r << endl;
}
