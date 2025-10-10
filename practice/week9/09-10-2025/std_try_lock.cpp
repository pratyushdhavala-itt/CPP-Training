#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1, m2;

void task1() {
    int result = std::try_lock(m1, m2);
    if (result == -1) {
        std::cout << "Task 1 got both locks\n";
        // critical section
        m1.unlock();
        m2.unlock();
    } else {
        std::cout << "Task 1 failed to lock mutex " << result << std::endl;
    }
}

void task2() {
    int result = std::try_lock(m2, m1); 
    if (result == -1) {
        std::cout << "Task 2 got both locks\n";
        // critical section
        m2.unlock();
        m1.unlock();
    } else {
        std::cout << "Task 2 failed to lock mutex " << result << std::endl;
    }
}

int main() {
    std::thread t1(task1);
    std::thread t2(task2);
    t1.join();
    t2.join();
}
