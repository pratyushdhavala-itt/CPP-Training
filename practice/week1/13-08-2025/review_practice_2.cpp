#include <iostream>
using namespace std;

int main() {

    int a[] {1, 2, 3, 4, 5};
    int b[] = {6, 7, 8, 9, 10};
    int *c = a;
    c = b;

    cout << a << endl;
    cout << b[2] << endl;
    cout << *c << endl;

    cout << sizeof(c) << endl;
    cout << sizeof(a) / sizeof(a[0]) << endl;

    cout << c[-4] << endl;

    //const int *d {&a};

    int e[5];

    cout << e[1] << endl;

    //char s1[5] = "Hello"; too long

    cout << "h" << 2[b] << endl;


    int (*f)[5] = &a;
    cout << *f[0] << endl;

    for (int i : *f) {

        cout << i;
    }

    cout << size(*f) << endl;

    int g[][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    cout << size(g) << endl;

    int (*h)[3] = g;

    int *i = a;
    cout << g << endl;
    cout << h << endl;

    cout << h[0][1] << endl;
    cout << i[0] << endl;


    cout << typeid(g).name() << endl;
    int (*j)[3][3] = &g;
    int (*k)[3] = g;

    cout << "J: " << typeid(j).name() << endl;

    cout << "K: " << typeid(k).name() << endl;

    cout << typeid(k).name() << endl;

    cout << *j[0][2] << endl;

    cout << *(k + 1)[0] << endl;

    int l[3][3] {};

    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         std::cin >> l[i][j];
    //     }
    // }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << l[i][j] << " ";
        }
        std::cout << '\n';
    }

    int *q = &g[0][0];
    
    cout << *(q + 7) << endl;
}

