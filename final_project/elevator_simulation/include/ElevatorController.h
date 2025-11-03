#ifndef ELEVATOR_CONTROLLER_H
#define ELEVATOR_CONTROLLER_H

#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include "Elevator.h"
#include "ElevatorRequest.h"

class ElevatorController {

private:

    int elevatorCount;
    std::mutex controllerMutex;
    std::condition_variable controllerCV;
    std::vector<Elevator*>& elevators;
    std::vector<std::thread> elevatorThreads;
    std::queue<ElevatorRequest> commonElevatorQueue;
    std::atomic<bool> stopSignal;
    ElevatorRequest storeRequest;

public:

    ElevatorController(std::vector<Elevator*>& elevators);
    void runElevatorThreads();
    void runElevatorController();
    bool waitAndGetElevatorRequest(ElevatorRequest& request);
    void assignRequestToSuitableElevator(const ElevatorRequest& request);
    void addRequestToQueue(ElevatorRequest request);
    virtual int calculateScore(Elevator& elevator, const ElevatorRequest& request);
    virtual bool canAssignRequestToElevator(Elevator& elevator, const ElevatorRequest& request);
    virtual void delayRequest(const ElevatorRequest& request);
    void changeDestinationFloor(int personId, int newDestinationFloor);
    void stopElevatorController();
    
    ~ElevatorController();
};

#endif