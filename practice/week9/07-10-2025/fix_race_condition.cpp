#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex mtx;

void increment() {
    for (int i = 0; i < 1000000; ++i) {
        mtx.lock();
        ++counter;
        mtx.unlock();
    } 
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.detach();
    t2.detach();

    std::cout << "Counter: " << counter << std::endl;
}