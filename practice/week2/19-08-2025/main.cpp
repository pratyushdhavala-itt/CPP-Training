#include "source.hpp"
#include <iostream>

int sub(int a, int b);
int sub(int a, int b);
int main() {
    //std::cout << add(2, 3) << std::endl;

    std::cout << sub(20, 10) << std::endl;

    char str[20] = "Hello";
    int i = sizeof(str) / sizeof(str[0]);

    

    std::cout << i << std::endl;
    return 0;
}

int sub(int a, int b) {
    return a - b;
}