#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <condition_variable>

std::mutex m1;
std::condition_variable cv;
bool pingTurn = true;

void ping() {

    for (int i = 0; i < 5; i++) {
        std::unique_lock<std::mutex> lock(m1);

        cv.wait(lock, [](){return pingTurn;});

        std::cout << "Ping" << std::endl;
        pingTurn = false;
        cv.notify_all();
    }
}

void pong() {

    for (int i = 0; i < 5; i++) {
        std::unique_lock<std::mutex> lock(m1);

        cv.wait(lock, [](){return !pingTurn;});

        std::cout << "Pong" << std::endl;
        pingTurn = true;
        cv.notify_all();
    }
}

int main() {

    std::thread t1(ping);
    std::thread t2(pong);

    t1.join();
    t2.join();
    
    return 0;
}