#include <iostream>
#include <thread>
#include "Lane.h"
#include "TrafficSignal.h"
#include "constants.h"

Lane::Lane(int id, int totalNumberOfCars, TrafficSignal* trafficSignal, std::mutex* printMutex) : id{id}, totalNumberOfCars{totalNumberOfCars}, trafficSignal{trafficSignal}, printMutex{printMutex} {
    numberOfCarsRemaining = totalNumberOfCars;
}

int Lane::getCarCount() const {
    return totalNumberOfCars;
}

int Lane::getCurrentCarCount() const {
    return numberOfCarsRemaining;
}

int Lane::getId() const {
    return id;
}

void Lane::crossTrafficSignal() {
    while (numberOfCarsRemaining > 0) {
        trafficSignal->waitForGreenLight();

        while (trafficSignal->isGreenLight() && numberOfCarsRemaining > 0) {
            {
                std::lock_guard<std::mutex> lock(*printMutex);
                std::cout << PRINT_CAR << (totalNumberOfCars - numberOfCarsRemaining + 1) << PRINT_CAR_LANE << id << PRINT_PASSING << std::endl;
            }
            numberOfCarsRemaining--;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

TrafficSignal* Lane::getTrafficSignal() {
    return trafficSignal;
}

Lane::~Lane() {
    delete trafficSignal;
}