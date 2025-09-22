#include <iostream>
using namespace std;

int main() {
    int counter = 0;
    for (int i = 0; i < 5; i++) {
        counter += i;
        cout << "counter = " << counter << endl;
    }
    return 0;
}
