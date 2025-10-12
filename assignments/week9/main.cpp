#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <algorithm>
#include <cmath>
#include "TrafficSignal.h"
#include "Lane.h"
#include "constants.h"

void trafficLightController(std::vector<Lane*>& lanes, std::mutex& printMutex);

void inputNumberOfLanes(double& numberOfLanes);

int main() {
    int numberOfCarsPerLane;
    double numberOfLanes;
    std::mutex printMutex;
    std::vector<Lane*> lanes;
    std::vector<std::thread> laneThreads;

    inputNumberOfLanes(numberOfLanes);

    for (int i = 0; i < numberOfLanes; i++) {
        std::cout << PRINT_ENTER_NUMBER_OF_CARS << i + 1 << PRINT_COLON;
        std::cin >> numberOfCarsPerLane;
        lanes.push_back(new Lane(i + 1, numberOfCarsPerLane, new TrafficSignal(), &printMutex));
    }

    for (int i = 0; i < numberOfLanes; i++) {
        laneThreads.emplace_back(&Lane::crossTrafficSignal, lanes.at(i));
    }
    
    trafficLightController(lanes, printMutex);

    for (std::thread& t : laneThreads) {
        t.join();
    }

    return 0;
}

void trafficLightController(std::vector<Lane*>& lanes, std::mutex& printMutex) {
    int numberOfLanes = lanes.size();
    const int WAIT_TIME_SECONDS = 5;
    while (true) {
        bool allCarsPassed = true;
        for (Lane* lane : lanes) {
            if (lane->getCurrentCarCount() > 0) {
                allCarsPassed = false;
                break;
            }
        }

        if (allCarsPassed) break;

        std::sort(lanes.begin(), lanes.end(), [](Lane* laneOne, Lane* laneTwo) {
            return laneOne->getCurrentCarCount() > laneTwo->getCurrentCarCount();
        });

        for (Lane* lane : lanes) {
            if (lane->getCurrentCarCount() == 0) continue;

            lane->getTrafficSignal()->setGreenLight();
            {
                std::lock_guard<std::mutex> lock(printMutex);
                std::cout << PRINT_LINE_SEPARATOR << PRINT_LANE << lane->getId() << PRINT_GREEN_LIGHT << PRINT_LINE_SEPARATOR << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::seconds(WAIT_TIME_SECONDS));
            lane->getTrafficSignal()->setRedLight();
            
            {
                std::lock_guard<std::mutex> lock(printMutex);
                std::cout << PRINT_LINE_SEPARATOR << PRINT_LANE << lane->getId() << PRINT_RED_LIGHT << PRINT_LINE_SEPARATOR << std::endl;
            }
        }
    }
}

void inputNumberOfLanes(double& numberOfLanes) {

    char input[4];
    while (true) {
        std::cout << PRINT_ENTER_NUMBER_OF_LANES << std::endl;
        std::cin.getline(input, 4);
        if (std::cin.fail()) {
            std::cout << "Invalid input ! ! !" << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
        numberOfLanes = atof(input);
        if (numberOfLanes > 99 || numberOfLanes <= 0 || (numberOfLanes != std::floor(numberOfLanes))) {
            std::cout << "Input value too big or too less or is a decimal ! ! !" << std::endl;
            continue;
        }
        break;
    }
}
