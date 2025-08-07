#include <iostream>


//In this file, we explore all the data types in C++

int main() {

    //first data type: void
    //void is mostly used to define the return type of a function

    /* size of various data types

        bool - 1 byte
        char - 1 byte
        short - 2 bytes
        int - 4 bytes
        long - 4 bytes
        long long - 8 bytes
        float - 4 bytes
        double - 8 bytes
        long double - 8 bytes

    */

    // we can use sizeof() to find out the size of data types and variables

    std::cout << "Size of integer: " << sizeof(int) << " bytes" << std::endl;



    //Integer types

    short num1 = 127; // size: 8 bits, range: -128 to 127
    int num2 = 32767; //size: 32 bits, range: -32768 to 32767
    long long num2 = 100000000000; //size: 64 bits, range: huge

}
