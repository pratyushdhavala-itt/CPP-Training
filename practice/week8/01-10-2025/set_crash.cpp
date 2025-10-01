#include <iostream>
#include <set>
using namespace std;

int main() {
    set<int> s;
    for (int i = 0; i < 1000; i++) s.insert(i);

    auto it = s.begin();  // points to 0
    s.erase(0);           // erase key 0 → it is invalid

    // Do lots of inserts to force tree rebalancing and memory reuse
    for (int i = 1000; i < 2000; i++) s.insert(i);

    cout << *it << endl;  // UB: very likely to crash or print garbage
}
