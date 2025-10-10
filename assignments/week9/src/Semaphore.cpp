#include <condition_variable>
#include <thread>
#include <mutex>
#include <chrono>
#include "Semaphore.h"


Semaphore::Semaphore(TrafficSignal trafficSignal) : trafficSignal{trafficSignal} {}

void Semaphore::wait() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this]() { return trafficSignal == Semaphore::GREEN; });
    trafficSignal = TrafficSignal::RED;
}

void Semaphore::signal() {
    std::unique_lock<std::mutex> lock(mtx);
    trafficSignal = TrafficSignal::GREEN;
    cv.notify_one();
}