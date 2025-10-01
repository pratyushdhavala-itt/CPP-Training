#include <iostream>
#include <set>

using namespace std;

int main() {

    set<int> setOne;

    setOne = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
    
    for (auto i : setOne) {
        cout << i << endl;
    }
    return 0;
}