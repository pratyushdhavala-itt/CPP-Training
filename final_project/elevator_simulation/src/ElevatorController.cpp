#include <iostream>
#include <queue>
#include <map>
#include <thread>
#include <algorithm>
#include "ElevatorController.h"
#include "Elevator.h"
#include "ElevatorRequest.h"
#include "ElevatorException.h"
#include"constants.h"

ElevatorController::ElevatorController(std::vector<Elevator*>& elevators) : elevators{elevators}, stopSignal{false}, storeRequest{ElevatorRequest::UP, 0, 0} {

    elevatorCount = this->elevators.size();
}

void ElevatorController::runElevatorController() {
    runElevatorThreads();
    while (true) {
        bool receivedRequest = waitAndGetElevatorRequest(storeRequest);
        if (!receivedRequest) {
            break;
        }
        assignRequestToSuitableElevator(storeRequest);
    }
}

void ElevatorController::addRequestToQueue(ElevatorRequest request) {
    {
        std::lock_guard<std::mutex> lock(controllerMutex);
        commonElevatorQueue.push(request);
    }
    controllerCV.notify_all();
}

void ElevatorController::runElevatorThreads() {
    for (int i = 0; i < elevatorCount; i++) {
        elevatorThreads.emplace_back(&Elevator::runElevator, elevators[i]);
    }
}

bool ElevatorController::waitAndGetElevatorRequest(ElevatorRequest& request) {
    std::unique_lock<std::mutex> lock(controllerMutex);
    controllerCV.wait(lock, [&]() {
        return !commonElevatorQueue.empty() || stopSignal.load();
    });

    if (commonElevatorQueue.empty() && stopSignal.load()) {
        return false;
    }
    request = commonElevatorQueue.front();
    commonElevatorQueue.pop();
    return true;
}

void ElevatorController::assignRequestToSuitableElevator(const ElevatorRequest& request) {
    int mostSuitableScore = std::numeric_limits<int>::max();
    int mostSuitableIndex = std::numeric_limits<int>::max();
    for (int i = 0; i < elevatorCount; i++) {
        Elevator* elevator = elevators[i];

        if (!canAssignRequestToElevator(*elevator, request)) {
            continue;
        }
        int elevatorIndex = i;
        int elevatorScore = calculateScore(*elevator, request);
        if ((elevatorScore < mostSuitableScore) || 
        (elevatorScore == mostSuitableScore && elevatorIndex < mostSuitableIndex)) {
            mostSuitableScore = elevatorScore;
            mostSuitableIndex = elevatorIndex;
        }
    }
    if (mostSuitableIndex != std::numeric_limits<int>::max()) {
        elevators[mostSuitableIndex]->processElevatorRequest(request);
    } else {
        delayRequest(request);
    }
}

int ElevatorController::calculateScore(Elevator& elevator, const ElevatorRequest& request) {
    int elevatorScore = 0;
    Elevator::ElevatorState currentState = elevator.getElevatorState();
    elevatorScore += std::abs(elevator.getCurrentFloorNumber() - request.sourceFloor);

    if (currentState == Elevator::IDLE) {
        elevatorScore -= 1;
    }  else if ((currentState == Elevator::GOING_UP && request.direction == ElevatorRequest::UP) || 
        (currentState == Elevator::GOING_DOWN && request.direction == ElevatorRequest::DOWN)) {
            elevatorScore -= 4;
    } else {
        elevatorScore += 3;
    }

    elevatorScore += elevator.pendingRequests();

    return elevatorScore;
}

bool ElevatorController::canAssignRequestToElevator(Elevator& elevator, const ElevatorRequest& request) {
    Elevator::ElevatorState currentState = elevator.getElevatorState();
    int currentFloorNumber = elevator.getCurrentFloorNumber();
    if (currentState == Elevator::IDLE || currentState == Elevator::DEFAULT) return true;
    if (currentState == Elevator::GOING_UP) {
        return request.direction == ElevatorRequest::UP && request.sourceFloor >= currentFloorNumber;
    }
    if (currentState == Elevator::GOING_DOWN) {
        return request.direction == ElevatorRequest::DOWN && request.sourceFloor < currentFloorNumber;
    }
    return false;
}

void ElevatorController::delayRequest(const ElevatorRequest& request) {
    ElevatorRequest tempRequest = request;
    {
        std::lock_guard<std::mutex> lock(controllerMutex);
        commonElevatorQueue.push(tempRequest);
    }
    controllerCV.notify_one();
}

void ElevatorController::changeDestinationFloor(int personId, int newDestinationFloor) {
    for (int i = 0; i < elevatorCount; i++) {
        if (elevators[i]->personExistsInsideElevator(personId)) {
            elevators[i]->changePersonDestinationFloor(personId, newDestinationFloor);
            return;
        }
    }
    throw ElevatorException(PRINT_PERSON + std::to_string(personId) + PRINT_PERSON_NOT_INSIDE_ELEVATOR);
}

void ElevatorController::stopElevatorController() {
    std::unique_lock<std::mutex> lock(controllerMutex);
    stopSignal.store(true);
    for(int i = 0; i < elevatorCount; i++) {
        elevators[i]->stopElevator();
    }
    controllerCV.notify_all();
}

ElevatorController::~ElevatorController() {
    std::for_each(elevatorThreads.begin(), elevatorThreads.end(), [&](std::thread& t){
        t.join();
    });
}
