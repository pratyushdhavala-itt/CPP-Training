#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print(int x) {cout << x << endl;}
int main() {
    
    vector<int> vecOne{99, 56, 47, 32, 20, 11, 5, 0};

    // int x = 1;
    // for_each(vecOne.begin(), vecOne.end(), [x](int) {cout << x << endl;});

    //auto x = count(vecOne.begin(), vecOne.end(), 2);

    //auto x = count_if(vecOne.begin(), vecOne.end(), [](int x){return x % 2 == 0;});

    // auto it = find(vecOne.begin(), vecOne.end(), 7);

    // cout << it << endl;

    // cout << *vecOne.end() << endl;

    // cout << boolalpha << (it == vecOne.end()) << endl;

    // cout << typeid(*it).name() << endl;

    // cout << x << endl;

    // vector<int>::iterator it = find_if(vecOne.begin(), vecOne.end(), [](int x) {return x % 2 == 0;});

    // cout << *it << endl;

    // for_each(vecOne.begin(), vecOne.end(), [](int x){ cout << x << endl; });

    // sort(vecOne.begin(), vecOne.end());

    // for_each(vecOne.begin(), vecOne.end(), [](int x){ cout << x << endl; });


    vector<pair<int, int>> vecTwo {{1, 2}, {3, 1}, {2, 2}, {2, 1}, {3, 0}};

    // for_each(vecTwo.begin(), vecTwo.end(), [](pair<int, int>& p){ cout << p.first << " " << p.second << endl;});

    sort(vecTwo.begin(), vecTwo.end(), [](pair<int, int>& p1, pair<int, int>& p2){ return p1.first < p2.first; });

    for_each(vecTwo.begin(), vecTwo.end(), [](pair<int, int>& p){ cout << p.first << " " << p.second << endl;});

    return 0;
}