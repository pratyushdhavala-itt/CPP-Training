#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Ascending {
public:
    bool operator()(int a, int b) {

        return a > b;
    }
};

template <typename T>
class Print {
private:
    bool first = true;
public:
    void operator()(T a) {
        if (first) {
            cout << a;
            first = false;
        } else {
            cout << ", " << a;
        }
    }

    ~Print() {
        cout << '\n';
    }
};

int main() {
    
    list<int> l1 {1, 2, 3};
    vector<int> v1 {5, 4, 3, 2, 1};

    sort(v1.begin(), v1.end(), Ascending());
    for_each(v1.begin(), v1.end(), Print<int>());

    auto it = find(l1.begin(), l1.end(), 2);
    *it = 5;
    for_each(l1.begin(), l1.end(), Print<int>());

    copy(v1.rbegin(), v1.rend(), l1.begin());

    for_each(l1.begin(), l1.end(), Print<int>());

        
    for_each(v1.begin(), v1.end(), Print<int>());

    auto it_2 = remove(v1.begin(), v1.end(), 3);
    *it_2 = 99;
    v1.erase(it_2);
    for_each(v1.begin(), v1.end(), Print<int>());

    v1.insert(v1.begin() + 2, 3);

    for_each(v1.begin(), v1.end(), Print<int>());

    transform(v1.begin(), v1.end(), v1.begin(), [](int x){return x + 10;});

    for_each(v1.begin(), v1.end(), Print<int>());

    int sum = accumulate(v1.begin(), v1.end(), 0, [](int a, int b){return a + b;});

    cout << sum << endl;

    return 0;
}