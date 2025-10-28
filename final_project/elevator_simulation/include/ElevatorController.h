#ifndef ELEVATOR_CONTROLLER_H
#define ELEVATOR_CONTROLLER_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include "Elevator.h"
#include "ElevatorRequest.h"

class ElevatorController {

private:

    std::mutex* controllerMutex;
    std::condition_variable* controllerCV;
    Elevator& elevatorOne;
    Elevator& elevatorTwo;
    std::vector<std::thread> elevatorThreads;
    std::queue<ElevatorRequest> commonElevatorQueue;

public:

    ElevatorController(Elevator& elevatorOne, Elevator& elevatorTwo);
    void startElevatorController();
    void addRequestToQueue(ElevatorRequest request);
    void assignRequestToElevator(Elevator& elevator, ElevatorRequest& request);
    int calculateScore(Elevator& elevator, ElevatorRequest& request);
    bool canAssignRequestToElevator(Elevator& elevator, ElevatorRequest& request);
    void delayRequest(ElevatorRequest request);
    ~ElevatorController();
};

#endif