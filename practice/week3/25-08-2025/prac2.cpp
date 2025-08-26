#include <iostream>

int main() {

    // references (l-value reference)

    int x = 5;
    int& y = x;
    double a = 3.14;
    std::cout << x << y << std::endl;

    x++;
    std::cout << x << y << std::endl;

    y++;
    std::cout << x << y << std::endl;

    int& z = a; // error: cannot convert l-value reference of int& to a type double

    double& w = x; // error: cannot convert l-value reference of double& to a type int

    float f = 7.5;

    double& s = f;

    int& ref; // error: references have to be initialized



}