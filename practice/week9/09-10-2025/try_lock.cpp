#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx;

void worker(int id) {
    while (true) {

    if (mtx.try_lock()) {
        std::cout << "Thread " << id << " got the lock!\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        mtx.unlock();
    } else {
        std::cout << "Thread " << id << " could NOT get the lock.\n";
    }
}
}

int main() {
    std::thread t1(worker, 1);
    std::thread t2(worker, 2);

    t1.join();
    t2.join();
}
