#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

using namespace std;

int main() {

    vector<int> v1 {1, 2, 3, 4, 5};
    
    deque<int> d1 {1, 2, 3, 4, 5};

    list<int> l1 {1, 2, 3, 4, 5};

    set<int> s1 {1, 2, 3, 4, 5};

    unordered_set<int> us1 {1, 2, 3, 4, 5};

    map<int, int> m1 {{1, 2}, {2, 4}, {3, 6}, {4, 8}, {5, 10}};
    
    unordered_map<int, int> um1 {{1, 2}, {2, 4}, {3, 6}, {4, 8}, {5, 10}};

    v1.assign();
    v1.at();
    v1.back();
    v1.capacity();
    v1.data();
    v1.emplace();
    v1.erase();
    v1.empty();
    v1.reserve();
    v1.resize();
    v1.insert();
    v1.front();
    v1.pop_back();
    v1.push_back();
    v1.size();
    v1.clear();


    return 0;
}