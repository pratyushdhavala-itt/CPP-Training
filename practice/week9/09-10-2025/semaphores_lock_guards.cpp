#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

class Semaphore {

private:

    std::mutex mutex;
    int count;

public:

    Semaphore(int initialCount = 0) : count{initialCount} {}

    void wait() {
        while (true) {
            mutex.lock();
            if (count > 0) {
                count--;
                mutex.unlock();
                return;
            }
            mutex.unlock();
        }
    }

    void signal() {
        mutex.lock();
        count++;
        mutex.unlock();
    }
};

Semaphore sem(3);
std::mutex print_mutex;

void task(int id) {
    sem.wait();
    print_mutex.lock();
    std::cout << "Entered critical section: " << id << std::endl;
    print_mutex.unlock();
    sem.signal();
    print_mutex.lock();
    std::cout << "Left critical section: " << id << std::endl;
    print_mutex.unlock();
}

int main() {

    std::thread threads[6];

    for (int i = 0; i < 6; i++) {
        threads[i] = std::thread(task, i + 1);
    }

    for (int i = 0; i < 6; i++) {
        threads[i].join();
    }
}