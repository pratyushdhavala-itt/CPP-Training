#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main() {
    
    vector<int> v1 {10, 20, 30};
    vector<int> v2 {40, 50, 60};
    std::ostream_iterator<int> out (std::cout, " ");

    // copy(v1.begin(), v1.end(), out);

    copy(v1.begin(), v1.end(), back_inserter(v2));

    copy (v2.begin(), v2.end(), out);
    return 0;
}