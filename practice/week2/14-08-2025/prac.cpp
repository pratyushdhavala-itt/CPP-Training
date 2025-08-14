#include <iostream>
// void add();
int add() {

    std::cout << "Func 1" << std::endl;

    return 0;
}

int add (int a = 0) {
    std::cout << "Func 2" << std::endl;

    return 0;
}

int main() {

    add();

    add(20);
}

// int add() {

//     return 1;
// }

// void add() {

//     std::cout << 5 << std::endl;
// }