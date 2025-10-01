#include <iostream>
#include <map>
using namespace std;

int main() {
    
    map<int, int> mpp {{1, 1}, {2, 3}};

    map<int, int>::iterator it = mpp.begin();

    for (it; it != mpp.end(); it++) {
        cout << (*it).first << endl;
    }

    return 0;
}