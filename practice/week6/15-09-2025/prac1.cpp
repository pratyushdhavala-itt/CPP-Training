// gdb_demo.cpp
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int add(int a, int b) {
    int sum = a + b;
    return sum;
}

void process(vector<int>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        v[i] += 1;
    }
}

void crash() {
    int *p = nullptr;
    *p = 42; // segfault here
}

int main(int argc, char** argv) {
    int x = 2, y = 3;
    int z = add(x, y);
    cout << "z = " << z << endl;

    vector<int> v = {1,2,3,4,5};
    process(v);
    cout << "v[2] = " << v[2] << endl;

    if (argc > 1 && strcmp(argv[1], "crash") == 0) {
        crash();
    } else {
        cout << "Run with 'crash' to trigger segfault." << endl;
    }

    int counter = 0;
    for (int i = 0; i < 5; ++i) {
        counter += i;
    }
    cout << "counter = " << counter << endl;
    return 0;
}
