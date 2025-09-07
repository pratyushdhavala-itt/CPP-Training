#include <iostream>
using namespace std;



class Dollars {
private:
    int m_dollars{};
public:
    explicit Dollars(int d)  
        : m_dollars{d}
    {}

    int getDollars() const { return m_dollars; }
};

void print(Dollars d) {
    std::cout << "$" << d.getDollars();
}

int main() {
    print(5); 
    return 0;
}
