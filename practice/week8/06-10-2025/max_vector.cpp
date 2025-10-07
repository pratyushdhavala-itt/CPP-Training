#include <iostream>
#include <vector>

void func(long n) {

    try {
        std::vector<int> v;
        v.reserve(n);
        std::cout << "Allotted at: " << n << std::endl;
    } catch (const std::bad_alloc& b) {
        func(n - 1);
    }
}

int main() {
    long n = 100000000000;
    func(n);
    
    return 0;
}