#include <iostream>
using namespace std;

class Example {
public:
    int* p = new int(6);
};

int main() {

    int* m;
    Example* ex;
    {
        ex = new Example();
        m = ex->p;
        delete ex;
    }

    cout << (int*) (ex->p) << endl;
    cout << m << endl;
    
    return 0;
}