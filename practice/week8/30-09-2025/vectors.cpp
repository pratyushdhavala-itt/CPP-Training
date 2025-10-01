#include <iostream>
#include <vector>
using namespace std;

int main() {
    
    vector<int> vecOne;
    vecOne.reserve(100);

    for (int i = 0; i < 32; i++) {

        vecOne.push_back(i);
        cout << "Size: " << vecOne.size() << endl;
        cout << "Capacity: " << vecOne.capacity() << endl;
    }
    return 0;
}