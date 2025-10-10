#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

std::mutex m1, m2;

void task1() {

    std::lock_guard<std::mutex> lock1(m1);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::lock_guard<std::mutex> lock2(m2);
    std::cout << "Task 1 finished" << std::endl;
}

void task2() {
    std::lock_guard<std::mutex> lock2(m2);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::lock_guard<std::mutex> lock1(m1);
    std::cout << "Task 2 finished" << std::endl;

}

int main() {

    std::thread t1(task1);
    std::thread t2(task2);

    t1.join();
    t2.join();
    return 0;
}