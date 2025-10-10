#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <condition_variable>

class Semaphore {

public:

enum TrafficSignal {
    GREEN = 1,
    RED = 2,
};

private:

    std::mutex mtx;
    std::condition_variable cv;
    TrafficSignal trafficSignal;

public:

    Semaphore(TrafficSignal trafficSignal = GREEN);

    void wait();

    void signal();

};

#endif