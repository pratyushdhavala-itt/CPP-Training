#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include "ElevatorLogger.h"
#include "ElevatorRequest.h"

class Elevator {

public:
    enum ElevatorState {
        GOING_UP = 1,
        GOING_DOWN = 2,
        IDLE = 3,
    };

    enum PersonAction {
        GETTING_IN = 1,
        GETTING_OUT = 2,
    };

private:

    int elevatorId;
    ElevatorLogger& logger;
    ElevatorState currentState;
    int currentFloor;
    std::mutex* elevatorMutex;
    std::mutex* loggerMutex;
    std::condition_variable* elevatorCV;
    std::queue<ElevatorRequest> elevatorQueue;
    std::map<int, std::vector<std::pair<int, PersonAction>>> floorData;
    std::set<int> floorsToVisitWhileGoingUp;
    std::set<int> floorsToVisitWhileGoingDown;

public:

    Elevator(int elevatorId, ElevatorLogger& logger, std::mutex* loggerMutex);  
    void runElevator();
    int getCurrentFloor();
    ElevatorState getElevatorState();
    void moveToFloor(int destinationFloor);
    void addRequestToQueue(ElevatorRequest& request);
    void determineNextDirection();
    bool pendingRequests();
    int getPendingStops();
    void advanceElevatorToFirstRequestedFloor();
    void processRequestWhileMoving(ElevatorRequest& request);
};

#endif