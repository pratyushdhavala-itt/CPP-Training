#include <iostream>
using namespace std;

class Person {

    const char* const m_name;
    int m_age;

public:

    Person(const char* name, int age) : m_name {name}, m_age {age} {

    }

    const char* getName() {
        return m_name;
    }

    int getAge() {
        return m_age;
    }

};

int main() {
    
    Person p("Pratyush", 22);

    cout << p.getName() << endl;

    return 0;
}