#include <iostream>
#include <thread>
#include "Lane.h"
#include "TrafficSignal.h"
#include "WriteToFile.h"
#include "constants.h"

extern bool allCarsPassed;

Lane::Lane(int id, int totalNumberOfCars, TrafficSignal* trafficSignal, std::mutex* printMtx) : id{id}, totalNumberOfCars{totalNumberOfCars}, trafficSignal{trafficSignal}, printMtx{printMtx} {
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
    WriteToFile writer;
    while (!allCarsPassed) {
        trafficSignal->waitForGreenLight();

        while (trafficSignal->isGreenLight() && numberOfCarsRemaining > 0) {
            std::string passingCarToString = PRINT_CAR + std::to_string((totalNumberOfCars - numberOfCarsRemaining + 1)) + PRINT_CAR_LANE + std::to_string(id) + PRINT_PASSING;
            {
                std::unique_lock<std::mutex> lock(*printMtx);
                printCv.wait(lock, [&]() { return canWrite; });
                writer(passingCarToString, std::ios::app);
            }
            numberOfCarsRemaining--;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

TrafficSignal* Lane::getTrafficSignal() {
    return trafficSignal;
}

void Lane::addCars(int numberOfCarsToBeAdded) {
    totalNumberOfCars += numberOfCarsToBeAdded;
    numberOfCarsRemaining += numberOfCarsToBeAdded;
}