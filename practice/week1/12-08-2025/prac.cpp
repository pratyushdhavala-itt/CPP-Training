#include <iostream>

int calcSize(const char *str);

int main() {

    char str[] = "hello";
    char str1[] = "bye";

    int size_one = calcSize(str);
    int size_two = calcSize(str1);

    int new_size = size_one + size_two;

    // std::cout << new_size;
    char str2[new_size + 1];

    for (int i = 0; i <= new_size; i++) {

        if (i < size_one) {
            str2[i] = str[i];
        } else {
            //std::cout << str1[i - size_one];
            str2[i] = str1[i - size_one];
        }
        
    }

    for (int i = 0; i < new_size; i++) {
         std::cout << str2[i];
    }
}

int calcSize(const char *str) {

    int i = 0;
    while (str[i] != '\0') {
        i++;
    }

    return i;
}