#include <iostream>
using namespace std;


struct Counter {
    int count = 0;

    void operator()(int x) {
        if (x % 2 == 0)
            ++count;
    }
};

int main() {
    Counter c;
    for (int i = 1; i <= 10; ++i)
        c(i);

    cout << "Even numbers: " << c.count << endl;;
}
