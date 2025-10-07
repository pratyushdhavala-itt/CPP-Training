#include <iostream>
#include <list>
#include <algorithm>

int main() {
    
    std::list<int> l1 {1, 2, 3, 4};

    std::for_each(l1.begin(), l1.end(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    l1.assign({5, 6, 7, 8, 9});

    std::for_each(l1.begin(), l1.end(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    l1.emplace(l1.begin(), 4);
    std::for_each(l1.begin(), l1.end(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    l1.emplace_front(3);
    std::for_each(l1.begin(), l1.end(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    l1.emplace_back(10);
    std::for_each(l1.begin(), l1.end(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    l1.erase(l1.begin());
    std::for_each(l1.begin(), l1.end(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    std::list<int> l2 {1, 3, 7, 5, 9};
    std::list<int> l3 {2, 6, 4, 8, 10};

    l2.merge(l3);

    std::for_each(l2.begin(), l2.end(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    l2.remove(6);
    std::for_each(l2.begin(), l2.end(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    l2.reverse();
    std::for_each(l2.begin(), l2.end(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    l2.reverse();
    std::for_each(l2.begin(), l2.end(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    l2.resize(20);
    std::for_each(l2.begin(), l2.end(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    l2.remove_if([](int x) {return x == 0;});
    std::for_each(l2.begin(), l2.end(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    return 0;
}