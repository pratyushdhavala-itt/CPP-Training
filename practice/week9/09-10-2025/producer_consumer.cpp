#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <chrono>

int buffer = 0;
bool isFull = false;
std::mutex mtx;
std::condition_variable cv;

void producer() {
    for (int i = 0; i < 5; i++) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [](){return !isFull;});

        buffer = i;
        isFull = true;
        std::cout << "Producer produced: " << buffer << std::endl;

        lock.unlock();
        cv.notify_all();

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void consumer() {
    for (int i = 0; i < 5; i++) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [](){return isFull;});

        std::cout << "Consumer consumed: " << buffer << std::endl;
        isFull = false;

        lock.unlock();
        cv.notify_all();

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
int main() {
    
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
    
    return 0;
}