#include <iostream>
#include <thread>
#include <mutex>

std::mutex print_mutex;

void printChar(char c) {
    for (int i = 0; i < 5; i++) {
        std::lock_guard<std::mutex> lock(print_mutex);
        std::cout << c << std::endl;
    }
}

int main() {

    std::thread t1(printChar, 'A');
    std::thread t2(printChar, 'B');
    std::thread t3(printChar, 'C');

    t1.join();
    t2.join();
    t3.join();
    
    return 0;
}