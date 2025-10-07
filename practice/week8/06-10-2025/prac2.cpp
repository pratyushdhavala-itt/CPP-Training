#include <iostream>
#include <vector>
#include <iterator>  // for std::istream_iterator

int main() {
    std::vector<int> v;

    std::cout << "Enter numbers (Ctrl+D to stop): ";


    std::istream_iterator<int> start(std::cin); 
    std::istream_iterator<int> end;              


    v.assign(start, end);

    std::cout << "You entered:\n";
    for (int x : v) std::cout << x << " ";
}