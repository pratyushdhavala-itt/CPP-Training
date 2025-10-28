#include <iostream>
#include <queue>
#include <map>
#include <thread>
#include <algorithm>
#include "ElevatorController.h"
#include "Elevator.h"
#include "ElevatorRequest.h"

ElevatorController::ElevatorController(Elevator& elevatorOne, Elevator& elevatorTwo) : elevatorOne{elevatorOne}, elevatorTwo{elevatorTwo} {

    controllerMutex = new std::mutex;
    controllerCV = new std::condition_variable;
}

ElevatorController::~ElevatorController() {
    std::for_each(elevatorThreads.begin(), elevatorThreads.end(), [&](std::thread& t){
        t.join();
    });
}

void ElevatorController::addRequestToQueue(ElevatorRequest request) {
    {
        std::lock_guard<std::mutex> lock(*controllerMutex);
        commonElevatorQueue.push(request);
    }
    controllerCV->notify_one();
}

void ElevatorController::startElevatorController() {
    elevatorThreads.emplace_back(&Elevator::runElevator, &elevatorOne);
    elevatorThreads.emplace_back(&Elevator::runElevator, &elevatorTwo);
    while (true) {

        std::unique_lock<std::mutex> lock(*controllerMutex);
        controllerCV->wait(lock, [&]() {
            return !commonElevatorQueue.empty();
        });

        ElevatorRequest request = commonElevatorQueue.front();
        commonElevatorQueue.pop();

        lock.unlock();

        int elevatorOneScore = calculateScore(elevatorOne, request);
        int elevatorTwoScore = calculateScore(elevatorTwo, request);

        // std::cout << "Elevator One score: " << elevatorOneScore << std::endl;
        // std::cout << "Elevator Two score: " << elevatorTwoScore << std::endl;

        bool canAssignRequestToElevatorOne = canAssignRequestToElevator(elevatorOne, request);
        bool canAssignRequestToElevatorTwo = canAssignRequestToElevator(elevatorTwo, request);

        if (canAssignRequestToElevatorOne && (!canAssignRequestToElevatorTwo || (elevatorOneScore <= elevatorTwoScore))) {
            // std::cout << "Assigned to 1" << std::endl;
            assignRequestToElevator(elevatorOne, request);
        } else if (canAssignRequestToElevatorTwo && (!canAssignRequestToElevatorOne || (elevatorTwoScore < elevatorOneScore))) {
            // std::cout << "Assigned to 2" << std::endl;    
            assignRequestToElevator(elevatorTwo, request);
        } else {
            // std::cout << "Delayed" << std::endl;
            delayRequest(request);
        }
    }
}

void ElevatorController::assignRequestToElevator(Elevator& elevator, ElevatorRequest& request) {

    elevator.addRequestToQueue(request);
}

int ElevatorController::calculateScore(Elevator& elevator, ElevatorRequest& request) {

    int score = 0;

    score += std::abs(elevator.getCurrentFloor() - request.sourceFloor);

    if (elevator.getElevatorState() == Elevator::IDLE) {
        score -= 1;
    } else if ((elevator.getElevatorState() == Elevator::GOING_UP && request.direction == ElevatorRequest::UP) ||
        (elevator.getElevatorState() == Elevator::GOING_DOWN && request.direction == ElevatorRequest::DOWN)) {

        score -= 2;
    } else {
        score += 3;
    }

    score += elevator.getPendingStops();

    return score;
}

bool ElevatorController::canAssignRequestToElevator(Elevator& elevator, ElevatorRequest& request) {

    if (elevator.getElevatorState() == Elevator::IDLE) return true;

    if (elevator.getElevatorState() == Elevator::GOING_UP) {
        return request.direction == ElevatorRequest::UP && request.sourceFloor >= elevator.getCurrentFloor();
    }

    if (elevator.getElevatorState() == Elevator::GOING_DOWN) {
        return request.direction == ElevatorRequest::DOWN && request.sourceFloor < elevator.getCurrentFloor();
    }

    return false;
}

void ElevatorController::delayRequest(ElevatorRequest request) {
    {
        std::lock_guard<std::mutex> lock(*controllerMutex);
        commonElevatorQueue.push(request);
    }
    controllerCV->notify_one();
}