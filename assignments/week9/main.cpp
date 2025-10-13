#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include "TrafficController.h"
#include "TrafficSignal.h"
#include "Lane.h"
#include "constants.h"
#include "utility_functions.h"

int main() {

    std::cout << PRINT_WELCOME << std::endl;
    
    std::mutex printMtx;
    std::vector<Lane*> lanes;
    std::vector<std::thread> laneThreads;
    TrafficController trafficController(lanes, &printMtx);

    std::cout << PRINT_ENTER_NUMBER_OF_LANES;
    int numberOfLanes = inputChoice(1, 99, false);
    lanes.reserve(numberOfLanes);
    inputNumberOfCarsPerLane(lanes, &printMtx);

    for (int i = 0; i < numberOfLanes; i++) {
        laneThreads.emplace_back(&Lane::crossTrafficSignal, lanes.at(i));
    }
    
    std::thread trafficControllerThread(&TrafficController::controlTraffic, &trafficController);

    addMoreCars(lanes);

    for (std::thread& laneThread : laneThreads) {
        laneThread.join();
    }

    trafficControllerThread.join();

    return 0;
}

