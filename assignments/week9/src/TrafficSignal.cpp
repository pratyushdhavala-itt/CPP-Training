#include <condition_variable>
#include <thread>
#include <mutex>
#include <chrono>
#include "TrafficSignal.h"


TrafficSignal::TrafficSignal(TrafficLight trafficLight) : trafficLight{trafficLight} {}

void TrafficSignal::waitForGreenLight() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this]() { return trafficLight == GREEN; });
}

void TrafficSignal::setGreenLight() {
    std::unique_lock<std::mutex> lock(mtx);
    trafficLight = GREEN;
    cv.notify_one();
}

void TrafficSignal::setRedLight() {
    std::unique_lock<std::mutex> lock(mtx);
    trafficLight = RED;
}

bool TrafficSignal::isGreenLight() {
    std::unique_lock<std::mutex> lock(mtx);
    return trafficLight == GREEN;
}