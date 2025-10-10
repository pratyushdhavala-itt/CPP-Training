#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>


class Semaphore {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;


public:
    Semaphore(int initCount = 0) : count(initCount) {}

    void wait() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return count > 0; }); 
        --count;
    }

    void signal() {
        std::unique_lock<std::mutex> lock(mtx);
        ++count;
        cv.notify_one();
    }
};

Semaphore sem(3);  

void task(int id) {
    sem.wait();
    std::cout << "Thread " << id << " entered critical section\n";

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Thread " << id << " leaving critical section\n";
    sem.signal();
}

int main() {
    std::thread threads[6];
    for (int i = 0; i < 6; ++i)
        threads[i] = std::thread(task, i + 1);

    for (int i = 0; i < 6; ++i)
        threads[i].join();

    return 0;
}

