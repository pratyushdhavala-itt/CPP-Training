#include <iostream>

class Counter {
private:
    int m_count{};

public:
    Counter(int start = 0) : m_count{start} {}

    Counter& increment() {
        ++m_count;
        //return *this;  
    }

    void print() const {
        std::cout << "Count: " << this->m_count << '\n';
    }
};

int main() {
    Counter c(5);
    c.increment().increment().increment().print(); 
    return 0;
}
