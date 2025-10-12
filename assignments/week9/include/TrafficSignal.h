#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <condition_variable>

class TrafficSignal {

public:

enum TrafficLight {
    GREEN = 1,
    RED = 2,
};

private:

    std::mutex mtx;
    std::condition_variable cv;
    TrafficLight trafficLight;

public:

    TrafficSignal(TrafficLight trafficLight = RED);

    virtual void waitForGreenLight();

    virtual void setGreenLight();

    virtual bool isGreenLight();

    virtual void setRedLight();

};

#endif