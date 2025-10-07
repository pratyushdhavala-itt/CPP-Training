#include <iostream>
#include <vector>
#include <iterator>
#include <set>
using namespace std;

int main() {
    
    vector<int> v1 {1, 2, 3, 4};

    auto it = v1.begin() + 2;

    v1.insert(it, 10);

    for (auto it = v1.begin(); it != v1.end(); it++) {
        cout << *it << endl;
    }

    set<int> s1 {1, 2, 3};

    auto it_2 = s1.begin();

    cout << typeid(it_2).name();

    std::istream_iterator<int> start;

    return 0;
}