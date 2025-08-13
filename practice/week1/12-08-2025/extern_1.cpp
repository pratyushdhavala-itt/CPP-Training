#include <iostream>

extern int hello_itt; 

int main() {

    std::cout << hello_itt << '\n';

    return 0;
}