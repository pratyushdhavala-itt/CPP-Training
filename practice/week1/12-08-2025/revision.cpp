#include <iostream>

#define MY_NAME "Pratyush Dhavala"


struct Point {

    private:
        int x, y;

    public:
        int sum() {
            return x + y;
        }

        Point(int a, int b) {
            x = a;
            y = b;
        }

        ~Point() {
            std::cout << "Destroyed!!" << '\n';
        }
};

int main() {

    #if 0
    // initializations

    // Default-initialization
    int a;
    std::cout << a << std::endl;

    // Copy-initialization
    int b = 2;
    
    // Direct-initialization
    int c (3);

    // List-initialization
    int d {4};

   // int w1 { 4.5 }; // compile error: list-init does not allow narrowing conversion

    int w2 = 4.5;   // compiles: w2 copy-initialized to value 4
    int w3 (4.5);   // compiles: w3 direct-initialized to value 4

    int w4 {};
    w4 = 4.5;

    std::cout << MY_NAME << typeid(MY_NAME).name() << '\n';

    #endif

    #ifdef MY_NAME
    //std::cout << "its defined"; // will be compiled since PRINT_JOE is defined
    #endif

    char c = 'a';
    std::cout << c << '\n';

    int arr[5] {1, 2, 3, 4, 5};

    int *ptr = arr;

    std::cout << *(arr + 1) << '\n';

    Point s = { 0, 13};

    std::cout << s.sum() << '\n';

    std::cout << "SIZE" << sizeof(Point) << '\n';

    char str[] = "Hello ITT";

    std::cout << str << std::endl;

    std::string str1 = "Bye ITT";

    str1[0] = 'Y';

    std::cout << str1 << std::endl;

    for (char s : str) {
        std::cout << s << std::endl;
    }

    for (auto it = str1.begin(); it != str1.end(); ++it) {
        std::cout << *it << std::endl;
    }

    char *prat = "Pratyush";
    char dhav[] = "Dhavala";

    //*(prat + 1) = 'a';

    dhav[1] = 'a';
    std::cout << *(prat + 1) << '\n';
    std::cout << dhav << '\n';

    

}
