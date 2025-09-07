#include <iostream>
using namespace std;

class MyClass {
private:
    //static int s_private = 12;

    int a = 5;

public:
    //static int getPrivate() { return s_private; }

    void getInt() {
        static int b = 6;
        cout << b++ << endl;
    }

};

//int MyClass::s_private{20};

int main() {
    MyClass mc;
    mc.getInt();
    mc.getInt();
    MyClass mc1;
    mc1.getInt();
}
