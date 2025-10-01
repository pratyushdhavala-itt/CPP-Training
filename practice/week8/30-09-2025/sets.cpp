#include <iostream>
#include <set>

using namespace std;

int main() {

    set<int> setOne;

    setOne = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};

    set<int>::iterator it = setOne.begin();

    setOne.erase(it);

    cout << *it << endl;
    
    return 0;
}