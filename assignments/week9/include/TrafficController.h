#ifndef TRAFFIC_CONTROLLER_H
#define TRAFFIC_CONTROLLER_H

#include <vector>
#include <mutex>
#include "Lane.h"
#include "WriteToFile.h"

class TrafficController {

private:

std::vector<Lane*>& lanes;
std::mutex* printMtx;
const int TRAFFIC_WAIT_TIME_SECONDS = 3.5;

public:

    TrafficController(std::vector<Lane*>& lanes, std::mutex*);
    void controlTraffic();
    std::string allLanesStatusToString(int currentGreenLaneId);
    std::string remainingCarsStatusToString();
    void sortLanes();
    void writeSignalStatusToFile(IWriter& writer, Lane* lane);
    void writeRemainingCarStatusToFile(IWriter& writer, Lane* lane = nullptr);

};

#endif