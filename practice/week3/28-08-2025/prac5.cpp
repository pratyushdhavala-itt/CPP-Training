#include <iostream>
using namespace std;

int main() {
    

    int** arr = new int*[3];

    for (int i = 0; i < 3; i++) {

        arr[i] = new int[3];
    }

    
    return 0;
}