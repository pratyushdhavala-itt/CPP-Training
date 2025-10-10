#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include "Semaphore.h"
#include "Lane.h"

void trafficController(std::vector<Lane>& lanes, std::vector<Semaphore*>& signals);


int main() {
    int numberOfLanes;

    std::cout << "Enter number of lanes" << std::endl;
    std::cin >> numberOfLanes;

    std::mutex ioLock;
    std::vector<int> numberOfCarsPerLane(numberOfLanes);
    std::vector<Semaphore*> signals;
    std::vector<Lane> lanes;
    std::vector<std::thread> laneThreads;

    for (int i = 0; i < numberOfLanes; i++) {
        std::cout << "Enter number of cars in lane " << i + 1 << ": ";
        std::cin >> numberOfCarsPerLane.at(i);
    }

    for (int i = 0; i < numberOfLanes; i++) {
        signals.push_back(new Semaphore(Semaphore::RED));
    }

    for (int i = 0; i < numberOfLanes; i++) {
        lanes.emplace_back(i + 1, numberOfCarsPerLane.at(i), signals.at(i), ioLock);
    }

    for (int i = 0; i < numberOfLanes; i++) {
        laneThreads.emplace_back(&Lane::simulate, &lanes.at(i));
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    trafficController(lanes, signals);

    for (std::thread& t : laneThreads) {
        t.join();
    }

    return 0;
}

void trafficController(std::vector<Lane>& lanes, std::vector<Semaphore*>& signals) {

    while (true) {
        bool allCarsPassed = true;

        for (Lane& lane : lanes) {
            if (lane.getCarCount() > 0) {
                allCarsPassed = false;
                break;
            }
        }

        if (allCarsPassed) break;

        for (int i = 0; i < lanes.size(); i++) {
            if (lanes.at(i).getCarCount() == 0) {
                continue;
            }
            
            signals.at(i)->signal();
            std::this_thread::sleep_for(std::chrono::seconds(5));

        }
    }
}