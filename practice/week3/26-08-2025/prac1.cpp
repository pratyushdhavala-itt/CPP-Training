#include <iostream>
#include <cstddef>

void print(int* ptr) {

    if (ptr) {
        std::cout << "called pointer: " << *ptr << std::endl;
    } else {
        std::cout << "null ptr called" << std::endl;
    }
}

void print(int ptr) {
    std::cout << "called int: " << ptr << std::endl;
}

void printTwo(int a = 0) {
    std::cout << "HELLO" << std::endl;
}

int main() {

    int* ptr1 = nullptr;
    int* ptr2 {};
    int* ptr3 = ptr1;

    std::cout << ptr1 << std::endl;
    std::cout << ptr2 << std::endl;
    std::cout << ptr3 << std::endl;

    int* ptr4;

    {
        int x = 5;
        ptr4 = &x;
        std::cout << *ptr4 << std::endl;
    }
    std::cout << *ptr4 << std::endl;
    std::cout << *ptr4 << std::endl;


    ptr3 = ptr4;

    std::cout << "HI" << *ptr3 << std::endl;

    print(0);
    // print(NULL); -> error: ambiguous call

    // int& x = {5};

    


}