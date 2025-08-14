#include <iostream>
#define MY_NAME "Pratyush" 
#define PI 22.0

using namespace std;
#define FUNCTION(name, a) a
#define F(X) #X "H"

#define MAX(a, b) a < b ? a : b

#ifndef SIZE
#define SIZE 10
#endif

int max(int a, int b) {return a < b ? a : b;}

// int foo();

//constexpr double PI = 22.0;


int main() {

    cout << SIZE << endl;

    const char *str;

    // cout << str << endl;

    // difference between using macros and constexpr
    // macros are just expression used for substitution

    double pi = PI;

    cout << pi << '\n';

    cout << 1 / PI << '\n';

    cout << pi << '\n';

    cout << 1 / pi << '\n';

    cout << F(2) << '\n';

    // std::cout << "print" << foo() << '\n';

    int x = 1;
    int y = 1;

    int a = MAX(x++, y++);

    cout << FUNCTION(a, 5) << endl;

    
}

// int foo() {
//     int PI = 654;
//     double pi = 543;
//     return PI;
// }