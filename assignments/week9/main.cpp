#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <algorithm>
#include <cmath>
#include "TrafficController.h"
#include "TrafficSignal.h"
#include "Lane.h"
#include "constants.h"

int inputChoice(int minChoice, int maxChoice);
void inputNumberOfCarsPerLane(std::vector<Lane*>& lanes, std::mutex* printMtx);
void addMoreCars(std::vector<Lane*>& lanes);
extern bool allCarsPassed;

int main() {

    std::cout << "Welcome to Traffic Light System Simulation\nInstructions:-\n   1. You can enter the number of cars to be added to a specific lane.\n   2. If you want to end the simulation, enter (-1) in the lane input, the simulation will be stopped after all the cars have passed." << std::endl;
    
    std::mutex printMtx;
    std::vector<Lane*> lanes;
    std::vector<std::thread> laneThreads;
    TrafficController trafficController(lanes, &printMtx);

    std::cout << PRINT_ENTER_NUMBER_OF_LANES;
    int numberOfLanes = inputChoice(1, 99);
    lanes.reserve(numberOfLanes);
    inputNumberOfCarsPerLane(lanes, &printMtx);

    for (int i = 0; i < numberOfLanes; i++) {
        laneThreads.emplace_back(&Lane::crossTrafficSignal, lanes.at(i));
    }
    
    std::thread t2(&TrafficController::controlTraffic, &trafficController);

    addMoreCars(lanes);

    for (std::thread& t : laneThreads) {
        t.join();
    }
    t2.join();

    return 0;
}

void addMoreCars(std::vector<Lane*>& lanes) {
    int laneNumber;
    int numberOfCarsToBeAdded;
        while (true) {
        std::cout << "Enter the lane number for more cars to be added to or enter (-1) to exit after all cars pass: ";
        laneNumber = inputChoice(1, lanes.size());
        if (laneNumber == -1) {
            allCarsPassed = true;
            return;
        }
        std::cout << "Enter the number of cars to be added: ";
        numberOfCarsToBeAdded = inputChoice(1, 99);
        lanes[laneNumber - 1]->addCars(numberOfCarsToBeAdded);
    }
}

void inputNumberOfCarsPerLane(std::vector<Lane*>& lanes, std::mutex* printMtx) {
    int numberOfCarsPerLane;
    for (int i = 0; i < lanes.capacity(); i++) {
        std::cout << PRINT_ENTER_NUMBER_OF_CARS << i + 1 << PRINT_COLON;
        numberOfCarsPerLane = inputChoice(1, 99);
        lanes.push_back(new Lane(i + 1, numberOfCarsPerLane, new TrafficSignal(), printMtx));
    }
}

int inputChoice(int minChoice, int maxChoice) {
    char c[3];
    double choice;
    while (true) {
        std::cin.getline(c, 3);
        if (std::cin.fail()) {
            std::cout << "invalid input1" << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
        choice = atof(c);
        if (choice == -1) return -1;
        if (choice < minChoice || choice > maxChoice || std::floor(choice) != choice) {
            std::cout << "invalid input2" << std::endl;
            continue;
        }
        break;
    }
    return choice;
}