#include <iostream>

int main() {

    std::cout << "Size of short int: " << sizeof(short) << std::endl;
    std::cout << "Size of int: " << sizeof(int) << std::endl;
    std::cout << "Size of long int: " << sizeof(long) << std::endl;
    std::cout << "Size of long long int: " << sizeof(long long) << std::endl;

    std::cout << "Size of void " << sizeof(void) << std::endl;

    /*ranges for data types

        short: -128 to 127
        int: -32768 to 32767
        long: huge
    */

    //example of overflow

    short num1 = 40000;

    std::cout << "num1: " << num1 << std::endl;


    //unsigned integers
    unsigned short num2 = 130;
    std::cout <<"num2: " << num2 << std::endl;

    //fixed sized integers
    std::cout << "Size of int8_t: " << sizeof(std::int8_t) << std::endl;
    std::cout << "Size of uint8_t: " << sizeof(std::uint8_t) << std::endl;
    std::cout << "Size of int16_t: " << sizeof(std::int16_t) << std::endl;
    std::cout << "Size of int32_t: " << sizeof(std::int32_t) << std::endl;
    std::cout << "Size of int64_t: " << sizeof(std::int64_t) << std::endl;

    std::int8_t x = 65;
    std::cout << (int) 'A' << std::endl;

    

}