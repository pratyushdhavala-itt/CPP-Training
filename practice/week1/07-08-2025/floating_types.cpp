#include <iostream>
#include <typeinfo>

int main() {

    std::cout << "Size of float: " << sizeof(float) << std::endl; //single precision
    std::cout << "Size of double: " << sizeof(double) << std::endl; //double precision
    std::cout << "Size of long double: " << sizeof(long double) << std::endl; //quadruple precision
    
    float x = 1;
    std::cout << typeid(x).name() << std::endl;

    std::cout << 1.23456789 << std::endl;

    std::cout << '\\' << std::endl;
}