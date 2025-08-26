#include <iostream>

int main() {

    int x = 3; // l-value and r-value -> error

    x + 1 = 5; // r-value and r-value -> error

    5 = 5; // r -value and r-value -> error

    int y = x; // l-value and l-value converted to r-value -> no error

    return 0;
}