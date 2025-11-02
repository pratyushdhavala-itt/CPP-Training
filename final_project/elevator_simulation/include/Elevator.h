#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <atomic>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <map>
#include <list>
#include <set>
#include "ElevatorLogger.h"
#include "ElevatorRequest.h"
#include "Floor.h"

class Elevator {

public:
    enum ElevatorState {
        GOING_UP = 1,
        GOING_DOWN = 2,
        IDLE = 3,
    };

private:

    int elevatorId;
    ElevatorLogger& logger;
    ElevatorState currentElevatorState;
    std::vector<Floor>::iterator currentFloorIterator;
    std::mutex loggerMutex;
    std::mutex elevatorMutex;
    std::condition_variable elevatorCV;
    std::vector<int> personsInsideElevator;
    std::vector<Floor> floors;
    std::set<int> upQueue;
    std::set<int, std::greater<int>> downQueue;
    std::atomic<bool> stopSignal;

public:

    Elevator(int elevatorId, ElevatorLogger& logger);  
    void runElevator();
    ElevatorState getElevatorState();
    void performActionOnCurrentFloor();
    void openElevatorDoors();
    void closeElevatorDoors();
    template <typename SetType>
    void moveElevator(SetType& queue);
    int getCurrentFloorNumber();
    std::vector<std::pair<int, Floor::PersonAction>>& getCurrentFloorPersonActions();
    void addPersonActionToFloor(int floorNumber, int personId, Floor::PersonAction action);
    void processElevatorRequest(const ElevatorRequest& request);
    void changePersonDestinationFloor(int personId, int newDestinationFloor);
    bool personExistsInsideElevator(int personId);
    void removePersonFromElevator(int personId);
    int pendingRequests();
    void stopElevator();
    void waitForElevatorRequest();
    void setCurrentElevatorState(ElevatorState elevatorState);
};

#endif