#ifndef LANE_H
#define LANE_H

#include "Semaphore.h"

class Lane {

private:

    int id;
    int numberOfCars;
    Semaphore& signal;
    std::mutex& ioLock;

public:

    Lane(int id, int numberOfCars, Semaphore* signal, std::mutex& ioLock);

    int getCarCount() const;

    int getId() const;

    void simulate();

};

#endif