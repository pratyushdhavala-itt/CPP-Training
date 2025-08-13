#include <iostream>
#include <cstring>
using namespace std;

int main() {

    char *str_1 {"Pratyush"};
    char str_2[] = "Pratyush";

    str_1 = "Dhavala";
    
    cout << *str_1 << endl;
    cout << str_2 << endl;

    str_1 = str_2;

    str_1[2] = 'F';

    char * const str_3 = str_1;

    str_3[2] = 'a';

    const char * const str_4 = str_3;

    cout << str_1 << endl;
    cout << str_2 << endl;

    cout << typeid(str_1[0]).name() << endl;

    cout << strlen(str_1) << endl;
    cout << strlen(str_2) << endl;
}