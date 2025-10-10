#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex m1, m2;

void task1() {
    while (true) {
        if (m1.try_lock()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            if (m2.try_lock()) {
                std::cout << "Task 1 got both locks\n";
                m2.unlock();
                m1.unlock();
                break;
            } else {
                m1.unlock();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void task2() {
    while (true) {
        if (m2.try_lock()) {
            // std::this_thread::sleep_for(std::chrono::milliseconds(10));
            if (m1.try_lock()) {
                std::cout << "Task 2 got both locks\n";
                m1.unlock();
                m2.unlock();
                break;
            } else {
                m2.unlock();
            }
        }
        // std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

int main() {
    std::thread t1(task1);
    std::thread t2(task2);
    t1.join();
    t2.join();
}
