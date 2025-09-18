#include <iostream>

struct Test {
    std::string name;
    Test(std::string n) : name{n} {
        std::cout << "Constructing " << name << '\n';
    }
    ~Test() {
        std::cout << "Destructing " << name << '\n';
    }
};

void g() {
    Test t1("t1");
    Test t2("t2");
    throw std::runtime_error("Something went wrong in g()");
}

int main() {
    
    try {
        int a = 3 / 0;

    }
    catch () {
        std::cout << "Caught exception:";
    }

    std::cout << "hello" << std::endl;


}
