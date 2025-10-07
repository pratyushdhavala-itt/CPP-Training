#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    
    std::vector v {1, 2, 3};
    std::cout << typeid(v[1]).name() << std::endl;

    for (auto it = v.begin(); it != v.end(); it++) {
        std::cout << *it << std::endl;
    }

    v.assign({8, 9, 10});

    for (auto it = v.begin(); it != v.end(); it++) {
        std::cout << *it << std::endl;
    }

    std::cout << "Index at 0: " << v[0] << std::endl; //does not throw

    std::cout << "Index at 0: " << v.at(0) << std::endl; //throws

    std::cout << "Back: " << v.back() << std::endl;

    v.back() = 40;

    std::cout << "Back: " << v.back() << std::endl;

    v.at(v.size() - 1) = 30;

    std::cout << "Back: " << v.back() << std::endl;

    std::cout << "First element through iterator: " << *v.begin() << std::endl;

    std::cout << "Capacity of v: " << v.capacity() << std::endl;

    std::vector<int> v2;
    std::cout << "Capacity of v2: " << v2.capacity() << std::endl;

    // const auto& it = v.begin();
    // const auto& cit = v.cbegin();

    // *it = 4;
    // *cit = 4;

    std::for_each(v.cbegin(), v.cend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    v.clear();
    std::cout << "Capacity of v: " << v.capacity() << std::endl;
    std::cout << "Size of v: " << v.size() << std::endl;
    std::for_each(v.cbegin(), v.cend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    v.assign({20, 30, 40, 50});

    std::for_each(v.crbegin(), v.crend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    auto ptr = v.data();

    std::cout << typeid(ptr).name() << std::endl;

    v.emplace(v.cend(), 60);

    std::for_each(v.crbegin(), v.crend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    v.emplace_back(70);

    std::for_each(v.crbegin(), v.crend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    v.erase(v.cbegin());

    std::for_each(v.crbegin(), v.crend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';
    
    auto ptr1 = v.front();
    std::cout << typeid(ptr1).name() << std::endl;

    v.insert(v.cbegin(), 20);
    std::for_each(v.crbegin(), v.crend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    std::cout << v.max_size() << std::endl;

    std::vector<int> v3;

    v3.operator=(v);

    std::for_each(v3.crbegin(), v3.crend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    v.pop_back();

    std::for_each(v.crbegin(), v.crend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    v.push_back(70);

    std::for_each(v.crbegin(), v.crend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    v.resize(4);

    std::for_each(v.crbegin(), v.crend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    std::for_each(v.end(), v.end() + 10, [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    std::cout << "Capacity of v: " << v.capacity() << std::endl;
    v.shrink_to_fit();
    std::cout << "Capacity of v: " << v.capacity() << std::endl;

    auto it = std::find(v.rbegin(), v.rend(), 11);
    std::cout << *it << std::endl;

    auto it_2 = std::find_if(v.crbegin(), v.crend(), [](int x) {return (x % 3 == 0);});
    std::cout << *it_2 << std::endl;

    bool b = std::binary_search(v.cbegin(), v.cend(), 30);
    std::cout << b << std::endl;

    auto it_3 = std::lower_bound(v.cbegin(), v.cend(), 35);
    std::cout << *it_3 << std::endl;

    std::cout << "V3:" << std::endl;
    std::for_each(v3.cbegin(), v3.cend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';
    auto it_4 = v3.end();
    v3.reserve(20);
    std::copy(v.begin(), v.end(), std::back_inserter(v3));

    std::cout << "V3:" << std::endl;
    std::for_each(v3.cbegin(), v3.cend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    std::fill(v3.rbegin(), v3.rend(), 11);
    std::for_each(v3.cbegin(), v3.cend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    std::generate(v3.begin(), v3.end(), []() {
        static int x = 0;
        x++;
        return x;
    });

    std::for_each(v3.cbegin(), v3.cend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    std::replace(v3.begin(), v3.end(), 10, 11);
    std::for_each(v3.cbegin(), v3.cend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    std::replace_if(v3.begin(), v3.end(), [](int x) {return (x % 2 == 0);}, 99);
    std::for_each(v3.cbegin(), v3.cend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    auto it_5 = std::remove(v3.begin(), v3.end(), 99);
    std::for_each(v3.cbegin(), v3.cend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    v3.erase(it_5, v3.cend());
    std::for_each(v3.cbegin(), v3.cend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    v3.insert(v3.end(), {2, 4, 6, 8, 10});

    it_5 = std::remove_if(v3.begin(), v3.end(), [](int x){return (x % 2 != 0);});
    v3.erase(it_5, v3.end());
    std::for_each(v3.cbegin(), v3.cend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    v3.insert(v3.end(), {5,5,5,5});
    std::for_each(v3.cbegin(), v3.cend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    it_5 = std::unique(v3.begin(), v3.end());
    
    v3.erase(it_5, v3.end());

    std::for_each(v3.cbegin(), v3.cend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    std::vector<int> v4 {10, 11, 12, 13, 14, 15};
    std::vector<int> v5 {10, 11, 13, 13, 14, 15};

    auto pair = std::mismatch(v4.begin(), v4.end(), v5.begin());
    std::cout << *pair.second << std::endl;

    v5.assign({1, 9, 3, 4, 8, 2, 6, 7});
    std::nth_element(v5.begin(), v5.begin() + 6, v5.end());

    std::for_each(v5.cbegin(), v5.cend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    std::partial_sort(v5.begin(), v5.begin() + 3, v5.end());
    std::for_each(v5.cbegin(), v5.cend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    v5.assign({1, 2, 3, 4, 5, 6, 7, 8, 9});
    auto it_7 = std::partition(v5.begin(), v5.end(), [](int x) {return (x % 2 == 0);});
    std::for_each(v5.begin(), it_7, [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    std::for_each(it_7, v5.end(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    std::for_each(v5.cbegin(), v5.cend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    std::sort(v5.begin(), v5.end());
    std::for_each(v5.cbegin(), v5.cend(), [](int x){std::cout << x << ", ";});
    std::cout << '\n';

    std::cout << std::accumulate(v5.begin(), v5.end(), 0, [](int x, int y) {return x + y;}) << std::endl;
    
    return 0;
}