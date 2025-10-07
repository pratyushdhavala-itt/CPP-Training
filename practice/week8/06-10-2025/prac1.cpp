#include <iostream>
#include <iterator>

int main() {
    std::cout << "Enter 3 numbers: ";
    std::istream_iterator<int> it(std::cin);  
    std::istream_iterator<int> end;       
    

    int val = *it;
    if (std::cin.fail()) {
        std::cout << "failed" << std::endl;
    }
    // it++;
    // int val2 = *it;
    // if (std::cin.fail()) {
    //     std::cout << "failed" << std::endl;
    // }
    // it++;
    // int val3 = *it;
    // if (std::cin.fail()) {
    //     std::cout << "failed" << std::endl;
    // }

    std::cout << *it << std::endl;
    std::cout << *it << std::endl;
    // std::cout << val2 << std::endl;
    // std::cout << val3 << std::endl;

    // while (it != end) {
    //     std::cout << *it << " next";  // read value
    //     ++it;                     // move to next
    // }
}