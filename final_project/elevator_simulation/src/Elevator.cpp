#include <iostream>
#include <bits/stdc++.h>
#include <thread>
#include <chrono>
#include <cmath>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include "Elevator.h"
#include "ElevatorRequest.h"
#include "ElevatorLogger.h"

Elevator::Elevator(int elevatorId, ElevatorLogger& logger) : elevatorId{elevatorId}, logger{logger}, currentElevatorState{IDLE} {
    for (int i = -2; i < 9; i++) {
        floors.emplace_back(i);
    }
    currentFloorIterator = floors.begin();
    std::advance(currentFloorIterator, 2);
}

void Elevator::runElevator() {
    while (true) {
        if (!pendingRequests() && stopSignal.load()) {
            break;
        } 
        waitForElevatorRequest();
        switch(currentElevatorState) {
            case GOING_UP:
                if (upQueue.empty()) {
                    if (!downQueue.empty()) {
                        setCurrentElevatorState(GOING_DOWN);
                    } else {
                        setCurrentElevatorState(IDLE);
                        continue;
                    }
                } else {
                    moveElevator(upQueue);
                }
                break;

            case GOING_DOWN:
                if (downQueue.empty()) {
                    if (!upQueue.empty()) {
                        setCurrentElevatorState(GOING_UP);
                    } else {
                        setCurrentElevatorState(IDLE);
                        continue;
                    }
                } else {
                    moveElevator(downQueue);
                }
                break;

            default:
                std::this_thread::sleep_for(std::chrono::seconds(1));
                break;
        }
    }
}

Elevator::ElevatorState Elevator::getElevatorState() {
    std::lock_guard<std::mutex> lock(elevatorMutex);
    return currentElevatorState;
}

void Elevator::openElevatorDoors() {
    std::string logOpenDoor;
    int currentFloor = currentFloorIterator->getFloorNumber();
    logOpenDoor = "[ELEVATOR " + std::to_string(elevatorId) + "]: " + "[FLOOR " + std::to_string(currentFloor) + "]: " + "OPENING DOORS";
    logger(elevatorId, currentFloor, logOpenDoor);
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Elevator::closeElevatorDoors() {
    std::string logCloseDoor;
    int currentFloor = currentFloorIterator->getFloorNumber();
    logCloseDoor = "[ELEVATOR " + std::to_string(elevatorId) + "]: " + "[FLOOR " + std::to_string(currentFloor) + "]: " + "CLOSING DOORS";
    logger(elevatorId, currentFloor, logCloseDoor);
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Elevator::performActionOnCurrentFloor() {
    bool openedDoors = false;
    std::string currentFloorAction;
    std::vector<std::pair<int, Floor::PersonAction>> actionsCopy = (*currentFloorIterator).getPersonActions();
    std::vector<int> removeIds;
    int currentFloor = getCurrentFloorNumber();
    for (std::pair<int, Floor::PersonAction>& p : actionsCopy) {
        if (p.second == Floor::GETTING_IN) {
            currentFloorAction = "[ELEVATOR " + std::to_string(elevatorId) + "]: " + "[FLOOR " + std::to_string(currentFloor) + "]: " + "PERSON " + std::to_string(p.first) + " STEPPING IN";
            personsInsideElevator.push_back(p.first);
            removeIds.push_back(p.first);
        } else if (p.second == Floor::GETTING_OUT && personExistsInsideElevator(p.first)) {
            currentFloorAction = "[ELEVATOR " + std::to_string(elevatorId) + "]: " + "[FLOOR " + std::to_string(currentFloor) + "]: " + "PERSON " + std::to_string(p.first) + " STEPPING OUT";
            removePersonFromElevator(p.first);
            removeIds.push_back(p.first);
        }
        if (!currentFloorAction.empty() && !openedDoors) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            openElevatorDoors();
            openedDoors = true;
        }
        if (!currentFloorAction.empty()) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            logger(elevatorId, currentFloor, currentFloorAction);
        }
        currentFloorAction.clear();
    }
    for (int id : removeIds) {
        (*currentFloorIterator).checkAndRemovePersonAction(id);
    }
    if (openedDoors) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        closeElevatorDoors();
    }
}

int Elevator::pendingRequests() {
    std::lock_guard<std::mutex> lock(elevatorMutex);
    return upQueue.size() + downQueue.size();
}

template<typename SetType>
void Elevator::moveElevator(SetType& queue) {
    std::string floorLogs;
    std::set<int>::iterator nextTargetFloorIt;
    while (true) {
        floorLogs = "[ELEVATOR " + std::to_string(elevatorId) + "]: " + "[FLOOR " + std::to_string(getCurrentFloorNumber()) + "]: ";
        {
            if (queue.empty()) {
                break;
            }
            nextTargetFloorIt = queue.begin();
            
            if (*nextTargetFloorIt > getCurrentFloorNumber()) {
                floorLogs += "MOVING UP";
                currentFloorIterator++;
            } else if (*nextTargetFloorIt < getCurrentFloorNumber()) {
                floorLogs += "MOVING DOWN";
                currentFloorIterator--;
            } else {
                performActionOnCurrentFloor();
                queue.erase(nextTargetFloorIt);
                continue;
            }
        }
        logger(elevatorId, getCurrentFloorNumber(), floorLogs);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int Elevator::getCurrentFloorNumber() {
    std::lock_guard<std::mutex> lock(elevatorMutex);
    return currentFloorIterator->getFloorNumber();
}

void Elevator::processElevatorRequest(const ElevatorRequest& request) {

    addPersonActionToFloor(request.sourceFloor, request.personId, Floor::GETTING_IN);
    addPersonActionToFloor(request.destinationFloor, request.personId, Floor::GETTING_OUT);

    if (request.direction == ElevatorRequest::UP) {
        elevatorMutex.lock();
        upQueue.insert(request.sourceFloor);
        upQueue.insert(request.destinationFloor);
        elevatorMutex.unlock();
        setCurrentElevatorState(GOING_UP);
        elevatorCV.notify_all();
    } else if (request.direction == ElevatorRequest::DOWN) {
        elevatorMutex.lock();
        downQueue.insert(request.sourceFloor);
        downQueue.insert(request.destinationFloor);
        elevatorMutex.unlock();
        setCurrentElevatorState(GOING_DOWN);
        elevatorCV.notify_all();
    }
}

void Elevator::addPersonActionToFloor(int floorNumber, int personId, Floor::PersonAction action) {
    std::vector<Floor>::iterator it = std::find_if(floors.begin(), floors.end(), [&](Floor& floor) {
        return floor.getFloorNumber() == floorNumber;
    });
    (*it).addPersonAction(personId, action);
}

void Elevator::changePersonDestinationFloor(int personId, int newDestinationFloor) {
    std::vector<Floor>::iterator it = std::find_if(floors.begin(), floors.end(), [&](Floor& floor) {
        return floor.checkAndRemovePersonAction(personId);
    });
    if ((*it).isFloorEmpty()) {
        if (currentElevatorState == GOING_UP) {
            upQueue.erase(upQueue.find((*it).getFloorNumber()));
        } else {
            downQueue.erase(downQueue.find((*it).getFloorNumber()));
        }
    }
    if (newDestinationFloor >= getCurrentFloorNumber()) {
        upQueue.insert(newDestinationFloor);
    } else {
        downQueue.insert(newDestinationFloor);
    }
    addPersonActionToFloor(newDestinationFloor, personId, Floor::GETTING_OUT);
}

bool Elevator::personExistsInsideElevator(int personId) {
    return std::find(personsInsideElevator.begin(), personsInsideElevator.end(), personId) != personsInsideElevator.end();
}

void Elevator::removePersonFromElevator(int personId) {
    std::vector<int>::iterator it = std::find(personsInsideElevator.begin(), personsInsideElevator.end(), personId);
    if (it != personsInsideElevator.end()) {
        personsInsideElevator.erase(it);
    }
}

void Elevator::stopElevator() {
    stopSignal.store(true);
}

void Elevator::waitForElevatorRequest() {

    std::unique_lock<std::mutex> lock(elevatorMutex);

    elevatorCV.wait_for(lock, std::chrono::seconds(10), [&]() {
        return (upQueue.size() + downQueue.size()) > 0;
    });

    lock.unlock();

    if ((upQueue.size() + downQueue.size()) == 0) {
        downQueue.insert(0);
        setCurrentElevatorState(GOING_DOWN);
    }
}

void Elevator::setCurrentElevatorState(ElevatorState elevatorState) {
    std::lock_guard<std::mutex> lock(elevatorMutex);
    currentElevatorState = elevatorState;
}