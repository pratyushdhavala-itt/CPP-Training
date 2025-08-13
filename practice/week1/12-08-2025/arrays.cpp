#include <iostream>

// void func_one(const char arr[]);

int main() {

    //array decay to pointer

    char arr[5] {'1', '2', '3'};

    auto ptr {arr};
    
    std::cout << std::boolalpha << (typeid(ptr) == typeid(int*)) << '\n';

    std::cout << std::boolalpha << (&arr[0] == ptr) << '\n';

    // arr[2] = 4;

    std::cout << "h" << arr[3] << '\n';

    std::cout << typeid(arr).name() << '\n';

    //arrays are not pointers, arrays decay into pointers
    //decay means loss of length type, pointer does not know the length of the array it is pointing to

    const char* ptr1 = (arr + 2);
    std::cout << "Ptr: " << ptr[0] << '\n';
    // func_one(arr);

    std::cout << "Size: " << sizeof(arr) << '\n';

    std::cout << "Size: " << sizeof(ptr) << '\n';

    std::cout << (ptr + 2)[0] << '\n';

    //iterate array with pointers
    constexpr int arr_1[] {9, 8, 7 ,6 ,5};
    const int* begin {arr_1};
    const int* end {arr_1 + std::size(arr_1)};

    for (; begin != end; begin++) {
        std::cout << *begin << '\n';
    }

    // c-style strings
    char str[] {"hello itt"};
    std::cout << str << '\n';

    char name[20];
    // std::cin >> name;
    std::cin.getline(name, std::size(name));
    std::cout << name << '\n';


}

// void func_one (const char arr[]) {

//     std::cout << arr[0] << '\n';
// }