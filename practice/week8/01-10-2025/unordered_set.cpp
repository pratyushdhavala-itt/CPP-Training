#include <iostream>
#include <unordered_set>
#include <algorithm>

const struct Sample {

    const int a;
    const char b;
};


int main() {
    
    std::unordered_set<int> set {144, 305, 983, 227, 1, 103, 99, 43, 81, 56, 31, 77};

    std::unordered_set<int>::iterator it = set.begin();

    set.erase(31);

    std::cout << *it << std::endl;

    // std::for_each(it, set.end(), [](int x){ std::cout << x << std::endl; });

    return 0;
}