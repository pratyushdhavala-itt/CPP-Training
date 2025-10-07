#include <iostream>
#include <map>
#include <algorithm>
#include <numeric>

int main() {

    std::map<int, int> m1 {{0, 0}, {1, 2}, {2, 4}, {3, 6}, {4, 8}};

    std::cout << m1.at(0) << std::endl;

    auto it = m1.begin();
    it++;
    std::cout << (it)->second << std::endl;
    
    std::for_each(m1.begin(), m1.end(), [](std::pair<int, int> p) {
        std::cout << "(" << p.first << ", " << p.second << ")" << ", ";
    });
    std::cout << '\n';

    m1.emplace(5, 10);

    std::for_each(m1.begin(), m1.end(), [](std::pair<int, int> p) {
        std::cout << "(" << p.first << ", " << p.second << ")" << ", ";
    });
    std::cout << '\n';

    m1.emplace(-1, -2);

    std::for_each(m1.begin(), m1.end(), [](std::pair<int, int> p) {
        std::cout << "(" << p.first << ", " << p.second << ")" << ", ";
    });
    std::cout << '\n';

    m1.emplace_hint(m1.end(), -2, -4);

    std::for_each(m1.begin(), m1.end(), [](std::pair<int, int> p) {
        std::cout << "(" << p.first << ", " << p.second << ")" << ", ";
    });
    std::cout << '\n';

    m1.emplace_hint(m1.end(), -2, -4);

    std::for_each(m1.begin(), m1.end(), [](std::pair<int, int> p) {
        std::cout << "(" << p.first << ", " << p.second << ")" << ", ";
    });
    std::cout << '\n';

    std::map<int, int>::node_type node = m1.extract(0);

    std::cout << node.key() << " " << node.mapped()<< std::endl;

    std::for_each(m1.begin(), m1.end(), [](std::pair<int, int> p) {
        std::cout << "(" << p.first << ", " << p.second << ")" << ", ";
    });
    std::cout << '\n';

    m1.insert({0, 0});

    std::for_each(m1.begin(), m1.end(), [](std::pair<int, int> p) {
        std::cout << "(" << p.first << ", " << p.second << ")" << ", ";
    });
    std::cout << '\n';

    m1.insert({0, 10});

    std::for_each(m1.begin(), m1.end(), [](std::pair<int, int> p) {
        std::cout << "(" << p.first << ", " << p.second << ")" << ", ";
    });
    std::cout << '\n';

    auto it_2 = std::find(m1.begin(), m1.end(), std::pair<const int, int>(5, 10));

    std::cout << it_2->second << std::endl;

    it_2 = std::find_if(m1.begin(), m1.end(), [](auto pa) {
        return pa.second == 8;
    });

    std::cout << it_2->first << std::endl;

    m1.erase(0);

    int b = std::accumulate(m1.begin(), m1.end(), 1, [] (int val, auto p) {
        val = val * p.second;
        return val;
    });

    std::cout << b << std::endl;

    std::transform(m1.begin(), m1.end(), m1.begin(), [] (auto p) {
        p.second = p.first;
        return std::make_pair(p.first, p.second);
    });

    std::for_each(m1.begin(), m1.end(), [](std::pair<int, int> p) {
        std::cout << "(" << p.first << ", " << p.second << ")" << ", ";
    });
    std::cout << '\n';

    return 0;
}