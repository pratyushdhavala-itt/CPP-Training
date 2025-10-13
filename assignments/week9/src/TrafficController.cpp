#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <algorithm>
#include <fstream>
#include "TrafficController.h"
#include "Lane.h"
#include "constants.h"
#include "WriteToFile.h"
#include "Writer.h"

extern bool allCarsPassed;

TrafficController::TrafficController(std::vector<Lane*>& lanes, std::mutex* printMtx) : lanes{lanes}, printMtx{printMtx} {}

void TrafficController::controlTraffic() {
    WriteToFile fileWriter;
    while (true) {
        if (allCarsPassed) break;
        sortLanes();
        for (Lane* lane : lanes) {
            writeRemainingCarStatusToFile(fileWriter, lane);
            if (lane->getCurrentCarCount() == 0) continue;
            writeSignalStatusToFile(fileWriter, lane);
            lane->getTrafficSignal()->setGreenLight();
            std::this_thread::sleep_for(std::chrono::seconds(TRAFFIC_WAIT_TIME_SECONDS));
            std::this_thread::sleep_for(std::chrono::seconds(2));
            lane->getTrafficSignal()->setRedLight();
        }
    }
}

void TrafficController::writeRemainingCarStatusToFile(IWriter& writer, Lane* lane) {
    std::string remainingCarsStatus = remainingCarsStatusToString();
    lane->canWrite = false;
    {
        std::unique_lock<std::mutex> lock(*printMtx);
        writer(remainingCarsStatus, std::ios::out);
    }
    lane->canWrite = true;
}

void TrafficController::writeSignalStatusToFile(IWriter& writer, Lane* lane) {
    std::string allLanesStatus = allLanesStatusToString(lane->getId());
    lane->canWrite = false;
    {
        std::unique_lock<std::mutex> lock(*printMtx);
        writer(allLanesStatus, std::ios::app);
    }
    lane->canWrite = true;
    lane->printCv.notify_all();
}

void TrafficController::sortLanes() {
    std::sort(lanes.begin(), lanes.end(), [](Lane* laneOne, Lane* laneTwo) {
        return laneOne->getCurrentCarCount() > laneTwo->getCurrentCarCount();
    });
}

std::string TrafficController::remainingCarsStatusToString() {
    std::string remainingCarsStatus = "\nRemaining cars in each lane:-\n";
    for (Lane* lane : lanes) {
        remainingCarsStatus += "Lane " + std::to_string(lane->getId()) + ": " + std::to_string(lane->getCurrentCarCount()) +" cars\n";
    }
    return remainingCarsStatus;
}

std::string TrafficController::allLanesStatusToString(int currentGreenLaneId) {
    int numberOfLanes = lanes.size();
    std::string allLanesStatus = "\nTraffic Lights of all the Lanes:-\n";
    for (int i = 0; i < numberOfLanes; i++) {
        if (i + 1 == currentGreenLaneId) {
            allLanesStatus += "LANE: " + std::to_string((i + 1)) + " -> GREEN\n";
        } else {
            allLanesStatus += "LANE: " + std::to_string((i + 1)) + " -> RED\n";
        }
    }
    return allLanesStatus;
}

