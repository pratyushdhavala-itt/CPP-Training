#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

class Copy {
private:
    int val;
public:

    Copy(int c = 0) : val{c} {
        cout << "constructed" << endl;
    }

    Copy(const Copy& c) {
        cout << "copied" << endl;
    }

    bool operator<(const Copy& other) const {
        return val < other.val;
    }

};

int main() {

    std::set<int> s1 {1 , 2, 1, 3, 2, 4};

    std::for_each(s1.begin(), s1.end(), [](int x) {
        cout << x << ", ";
    });
    cout << '\n';
    
    s1.insert(5);

    std::for_each(s1.begin(), s1.end(), [](int x) {cout << x << ", ";});
    cout << '\n';

    cout << *s1.find(2) << endl;

    if (s1.find(10) != s1.end()) {

    } else {
        cout << "not found" << endl;
    }

    std::set<Copy> s2;
    Copy c1(4);
    s2.insert(c1);

    s2.emplace(2);
    Copy c(3);
    s2.emplace(c);

    std::set<int>::node_type n = s1.extract(1);

    cout << n.

    return 0;
}