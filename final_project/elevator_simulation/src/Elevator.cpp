#include <iostream>
#include <bits/stdc++.h>
#include <thread>
#include <chrono>
#include <cmath>
#include <mutex>
#include <condition_variable>
#include "Elevator.h"
#include "ElevatorRequest.h"
#include "ElevatorLogger.h"

Elevator::Elevator(int elevatorId, ElevatorLogger& logger, std::mutex* loggerMutex) : elevatorId{elevatorId}, logger{logger}, currentState{IDLE}, loggerMutex{loggerMutex}, currentFloor{0} {
    for (int i = 0; i < 9; i++) {
        floorData.insert({i, std::vector<std::pair<int, Elevator::PersonAction>>()});
    }

    elevatorMutex = new std::mutex;
    elevatorCV = new std::condition_variable;
}

int Elevator::getCurrentFloor() {
    return currentFloor;
}

Elevator::ElevatorState Elevator::getElevatorState() {
    return currentState;
}

int Elevator::getPendingStops() {
    return floorsToVisitWhileGoingDown.size() + floorsToVisitWhileGoingUp.size();
}

bool Elevator::anyPendingRequests() {
    return !(floorsToVisitWhileGoingDown.empty() && floorsToVisitWhileGoingUp.empty());     
}

void Elevator::waitForElevatorRequest() {
    std::unique_lock<std::mutex> lock(*elevatorMutex);
    elevatorCV->wait(lock, [&](){
        return !elevatorQueue.empty() || anyPendingRequests();
    });
    ElevatorRequest request = elevatorQueue.front();
    elevatorQueue.pop();
    lock.unlock();
    processRequestWhileMoving(request);
}

void Elevator::runElevator() {
    while (true) {
        waitForElevatorRequest();
        determineNextDirection();
        // advanceElevatorToFirstRequestedFloor();
        switch(currentState) {
            int nextFloorStop;
            case GOING_UP:
                while (!floorsToVisitWhileGoingUp.empty()) {
                    nextFloorStop = *floorsToVisitWhileGoingUp.begin();
                    moveToFloor(nextFloorStop);
                    floorsToVisitWhileGoingUp.erase(nextFloorStop);
                }
                break;
            case GOING_DOWN:
                while (!floorsToVisitWhileGoingDown.empty()) {
                    nextFloorStop = *floorsToVisitWhileGoingDown.rbegin();
                    moveToFloor(nextFloorStop);
                    floorsToVisitWhileGoingDown.erase(nextFloorStop);
                }
                break;
            case IDLE:
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                break;
        }
        currentState = IDLE;
    }
}

void Elevator::determineNextDirection() {
    if (!anyPendingRequests()) {
        currentState = IDLE;
        return;
    }
    if (currentState == GOING_UP && !floorsToVisitWhileGoingUp.empty()) return;
    if (currentState == GOING_DOWN && !floorsToVisitWhileGoingDown.empty()) return;
    if (floorsToVisitWhileGoingUp.empty() && !floorsToVisitWhileGoingDown.empty()) {
        currentState = GOING_DOWN;
    } else if (floorsToVisitWhileGoingDown.empty() && !floorsToVisitWhileGoingUp.empty()) {
        currentState = GOING_UP;
    }
}

void Elevator::openElevatorDoors() {
    std::string logOpenDoor;
    logOpenDoor = "[ELEVATOR " + std::to_string(elevatorId) + "]: " + "[FLOOR " + std::to_string(currentFloor) + "]: " + "OPENING DOORS";
    {
        std::unique_lock<std::mutex> lock(*loggerMutex);
        logger(logOpenDoor);
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Elevator::closeElevatorDoors() {
    std::string logCloseDoor;
    logCloseDoor = "[ELEVATOR " + std::to_string(elevatorId) + "]: " + "[FLOOR " + std::to_string(currentFloor) + "]: " + "CLOSING DOORS";
    {
        std::unique_lock<std::mutex> lock(*loggerMutex);
        logger(logCloseDoor);
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Elevator::performActionOnCurrentFloor() {
    if (!floorData[currentFloor].empty()) {
        openElevatorDoors();
    }
    std::string currentFloorAction;
    std::vector<std::pair<int, PersonAction>>& actions = floorData[currentFloor];
    for (std::pair<int, PersonAction>& p : actions) {
        if (p.second == GETTING_IN) {
            currentFloorAction = "[ELEVATOR " + std::to_string(elevatorId) + "]: " + "[FLOOR " + std::to_string(currentFloor) + "]: " + "PERSON " + std::to_string(p.first) + " STEPPING IN";
        } else if (p.second == GETTING_OUT) {
            currentFloorAction = "[ELEVATOR " + std::to_string(elevatorId) + "]: " + "[FLOOR " + std::to_string(currentFloor) + "]: " + "PERSON " + std::to_string(p.first) + " STEPPING OUT";
        }
        {
            std::lock_guard<std::mutex> lock(*loggerMutex);
            logger(currentFloorAction);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    if (!floorData[currentFloor].empty()) {
        closeElevatorDoors();
    }
    actions.clear();
}

void Elevator::moveToFloor(int destinationFloor) {
    int directionToMove = (currentState == GOING_UP) ? 1 : -1;
    std::string floorLogs;
    while (currentFloor != destinationFloor) {
        currentFloor += directionToMove;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        floorLogs = "[ELEVATOR " + std::to_string(elevatorId) + "]: " + "[FLOOR " + std::to_string(currentFloor) + "]: ";
        if (directionToMove == 1) {
            floorLogs += "MOVING UP";
        } else {
            floorLogs += "MOVING DOWN";
        }
        {
            std::unique_lock<std::mutex> lock(*loggerMutex);
            logger(floorLogs);
        }
    }
    performActionOnCurrentFloor();
}

void Elevator::addRequestToQueue(ElevatorRequest& request) {
    ElevatorRequest newRequest = request;
    {
        std::lock_guard<std::mutex> lock(*elevatorMutex);
        elevatorQueue.push(newRequest);
    }
    elevatorCV->notify_one();
}

void Elevator::processRequestWhileMoving(ElevatorRequest& request) {
    floorData[request.sourceFloor].push_back({request.personId, GETTING_IN});
    floorData[request.destinationFloor].push_back({request.personId, GETTING_OUT});
    if (request.direction == ElevatorRequest::UP) {
        floorsToVisitWhileGoingUp.insert(request.sourceFloor);
        floorsToVisitWhileGoingUp.insert(request.destinationFloor);
    } else {
        floorsToVisitWhileGoingDown.insert(request.sourceFloor);
        floorsToVisitWhileGoingDown.insert(request.destinationFloor);
    }
}

void Elevator::advanceElevatorToFirstRequestedFloor() {
    if (!floorsToVisitWhileGoingUp.empty()) {
        int firstStop = *floorsToVisitWhileGoingUp.begin();
        if (firstStop != currentFloor) {
            currentState = (firstStop > currentFloor) ? GOING_UP : GOING_DOWN;
            moveToFloor(firstStop);
        }
    } else if (!floorsToVisitWhileGoingDown.empty()) {
        int firstStop = *floorsToVisitWhileGoingDown.rbegin();
        if (firstStop != currentFloor) {
            currentState = (firstStop > currentFloor) ? GOING_UP : GOING_DOWN;
            moveToFloor(firstStop);
        }
    }
}