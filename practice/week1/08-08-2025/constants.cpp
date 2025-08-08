#include <iostream>

//we can define consts using MACROS
#define MY_NAME "Pratyush"

//example for using const as a function parameter
void printInt(const int x);

//const as a return value of a function
//we should avoid it
const int getValue() {
    return 5;
}

int main() {

    //printing const value using defined macros
    std::cout << "My name is " << MY_NAME << std::endl;

    //two ways to declare a variable as a constant
    const double gravity = 9.8; //preffered
    int const sides = 4;

    //const variables must always be initialized
    //const double gravity;  -> gives error

    //const variables can be initialized from other variables too
    int age = 22;
    const int constAge = age;

    //naming convention for constants
    const int EARTH_GRAVITY = 9.8;
    const int kEarthGravity = 9.8;

    //const can be used as function parameters
    //function defined outside this scope
    printInt(5);
    printInt(6);

    std::cout << getValue() << std::endl;

    return 0;
    
}

void printInt(const int x) {
    std::cout << x << std::endl;
}



