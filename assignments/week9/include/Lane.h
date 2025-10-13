#ifndef LANE_H
#define LANE_H

#include "TrafficSignal.h"

class Lane {

private:

    int id;
    int totalNumberOfCars;
    int numberOfCarsRemaining;
    TrafficSignal* trafficSignal;
    std::mutex* printMtx;

public:

    std::condition_variable printCv;
    bool canWrite = false;

    Lane(int id, int numberOfCars, TrafficSignal* trafficSignal, std::mutex* printMutex);

    virtual int getCarCount() const;

    virtual int getCurrentCarCount() const;

    virtual int getId() const;

    virtual void crossTrafficSignal();

    virtual void addCars(int numberOfCarsToBeAdded);

    virtual TrafficSignal* getTrafficSignal();

    virtual ~Lane();

};

#endif