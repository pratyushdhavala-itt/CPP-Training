#include <iostream>

int main() {
    
    int a = 1;
    int b = 2;
    int* ptr1 = &a;
    int* ptr2 = &b;

    int* ptr;

    {
        int x = 4;
        ptr = &x;
        std::cout << ptr << std::endl;
    }

    int c = 3;
    int* ptr3 = &c;

    std::cout << ptr1 << std::endl;
    std::cout << ptr2 << std::endl;
    std::cout << ptr3 << std::endl;
    

    std::cout << *ptr << std::endl;
    return 0;
}