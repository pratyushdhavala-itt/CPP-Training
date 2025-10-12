#ifndef LANE_H
#define LANE_H

#include "TrafficSignal.h"

class Lane {

private:

    int id;
    int totalNumberOfCars;
    int numberOfCarsRemaining;
    TrafficSignal* trafficSignal;
    std::mutex* printMutex;

public:

    Lane(int id, int numberOfCars, TrafficSignal* trafficSignal, std::mutex* printMutex);

    int getCarCount() const;

    int getCurrentCarCount() const;

    int getId() const;

    void crossTrafficSignal();

    TrafficSignal* getTrafficSignal();

    ~Lane();

};

#endif