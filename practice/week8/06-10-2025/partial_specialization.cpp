#include <iostream>
using namespace std;

template<typename T>
class Display {
public:
    void show(T value) { std::cout << "Value: " << value << '\n'; }
};

template<typename T>
class Display<T*> {
public:
    void show (T* value) { std::cout << "Pointed value: " << *value << '\n';}
};

template <typename T1, typename T2>
class Pair {
    T1 first;
    T2 second;
public:
    Pair(T1 a, T2 b) : first(a), second(b) {}

    void display() const {
        cout << "Generic Pair: " << first << ", " << second << endl;
    }
};

template <typename T>
class Pair<T, bool> {
    T first;
    bool second;
public:
    Pair(T a, bool b) : first(a), second(b) {}

    void display() const {
        cout << boolalpha << "Generic Pair: " << first << ", " << second << endl;
    }
};

template <typename T>
class Pair<bool, T> {
    bool first;
    T second;
public:
    Pair(bool a, T b) : first(a), second(b) {}

    void display() const {
        cout << boolalpha << "Generic Pair: " << first << ", " << second << endl;
    }
};

int main() {
    int x = 42;
    Display<int> d1; 
    Display<int*> d2;  

    d1.show(x); 
    d2.show(&x);

    Pair p1(true, 3.6);  
    Pair p2(4, false);    
    p1.display();  
    p2.display();  
}
