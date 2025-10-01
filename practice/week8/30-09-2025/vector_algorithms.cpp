#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print(int x) {cout << x << endl;}
int main() {
    
    vector<int> vecOne{1, 2, 2, 3, 3, 3, 4, 6};

    // int x = 1;
    // for_each(vecOne.begin(), vecOne.end(), [x](int) {cout << x << endl;});

    //auto x = count(vecOne.begin(), vecOne.end(), 2);

    //auto x = count_if(vecOne.begin(), vecOne.end(), [](int x){return x % 2 == 0;});

    auto it = find(vecOne.begin(), vecOne.end(), 6);

    

    // cout << x << endl;
    return 0;
}