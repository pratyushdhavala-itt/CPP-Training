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
#include "constants.h"

Elevator::Elevator(int elevatorId, ElevatorLogger& logger) : elevatorId{elevatorId}, logger{logger}, currentElevatorState{IDLE}, stopSignal{false}, liftDelay{3} {
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
                handleGoingUp();
                break;

            case GOING_DOWN:
                handleGoingDown();
                break;

            case DEFAULT:
                moveElevatorDown();
                break;

            default:
                std::this_thread::sleep_for(std::chrono::seconds(1));
                break;
        }
    }
}

void Elevator::handleGoingUp() {
    if (getUpQueueSize() == 0) {
        if (getDownQueueSize() != 0) {
            setCurrentElevatorState(GOING_DOWN);
        } else {
            setCurrentElevatorState(IDLE);
        }
    } else {
        moveElevatorUp();
    }
}

void Elevator::handleGoingDown() {
    if (getDownQueueSize() == 0) {
        if (getUpQueueSize() != 0) {
            setCurrentElevatorState(GOING_UP);
        } else {
            setCurrentElevatorState(IDLE);
        }
    } else {
        moveElevatorDown();
    }
}

Elevator::ElevatorState Elevator::getElevatorState() {
    std::lock_guard<std::mutex> lock(elevatorMutex);
    return currentElevatorState;
}

void Elevator::openElevatorDoors() {
    std::string logOpenDoor;
    int currentFloor = currentFloorIterator->getFloorNumber();
    logOpenDoor = PRINT_LOG_ONE + std::to_string(elevatorId) + PRINT_LOG_TWO + PRINT_LOG_THREE + std::to_string(currentFloor) + PRINT_LOG_FOUR + PRINT_OPEN_DOORS;
    logger(elevatorId, currentFloor, logOpenDoor);
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Elevator::closeElevatorDoors() {
    std::string logCloseDoor;
    int currentFloor = currentFloorIterator->getFloorNumber();
    logCloseDoor = PRINT_LOG_ONE + std::to_string(elevatorId) + PRINT_LOG_TWO + PRINT_LOG_THREE + std::to_string(currentFloor) + PRINT_LOG_FOUR + PRINT_CLOSE_DOORS;
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
            currentFloorAction = PRINT_LOG_ONE + std::to_string(elevatorId) + PRINT_LOG_TWO + PRINT_LOG_THREE + std::to_string(currentFloor) + PRINT_LOG_FOUR + PRINT_PERSON_LOG + std::to_string(p.first) + PRINT_STEPPING_IN;
            personsInsideElevator.push_back(p.first);
            removeIds.push_back(p.first);
        } else if (p.second == Floor::GETTING_OUT && personExistsInsideElevator(p.first)) {
            currentFloorAction = PRINT_LOG_ONE + std::to_string(elevatorId) + PRINT_LOG_TWO + PRINT_LOG_THREE + std::to_string(currentFloor) + PRINT_LOG_FOUR + PRINT_PERSON_LOG + std::to_string(p.first) + PRINT_STEPPING_OUT;
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

    return getUpQueueSize() + getDownQueueSize();
}

template<typename SetType>
void Elevator::moveElevator(SetType& queue) {
    std::string floorLogs;
    std::set<int>::iterator nextTargetFloorIt;
    while (true) {
        floorLogs = PRINT_LOG_ONE + std::to_string(elevatorId) + PRINT_LOG_TWO + PRINT_LOG_THREE + std::to_string(getCurrentFloorNumber()) + PRINT_LOG_FOUR;
        
        if (queue.empty()) {
            break;
        }
        nextTargetFloorIt = queue.begin();
        
        if (*nextTargetFloorIt > getCurrentFloorNumber()) {
            floorLogs += PRINT_MOVING_UP;
            currentFloorIterator++;
        } else if (*nextTargetFloorIt < getCurrentFloorNumber()) {
            floorLogs += PRINT_MOVING_DOWN;
            currentFloorIterator--;
        } else {
            performActionOnCurrentFloor();
            queue.erase(nextTargetFloorIt);
            continue;
        }
    
        logger(elevatorId, getCurrentFloorNumber(), floorLogs);
        std::this_thread::sleep_for(std::chrono::seconds(liftDelay));
    }
}

int Elevator::getCurrentFloorNumber() {
    std::lock_guard<std::mutex> lock(elevatorMutex);
    return currentFloorIterator->getFloorNumber();
}

void Elevator::processElevatorRequest(const ElevatorRequest& request) {

    addPersonActionToFloor(request.sourceFloor, request.personId, Floor::GETTING_IN);
    addPersonActionToFloor(request.destinationFloor, request.personId, Floor::GETTING_OUT);

    if (getElevatorState() == Elevator::DEFAULT) {
        if (existsInDownQueue(0)) {
            removeFromDownQueue(0);
        }
    }

    if (request.direction == ElevatorRequest::UP) {
        addToUpQueue(request.sourceFloor);
        addToUpQueue(request.destinationFloor);
        setCurrentElevatorState(GOING_UP);
        elevatorCV.notify_all();
    } else if (request.direction == ElevatorRequest::DOWN) {
        addToDownQueue(request.sourceFloor);
        addToDownQueue(request.destinationFloor);
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
        if (getElevatorState() == GOING_UP) {
            removeFromUpQueue((*it).getFloorNumber());
        } else {
            removeFromDownQueue((*it).getFloorNumber());
        }
    }
    if (newDestinationFloor >= getCurrentFloorNumber()) {
        addToUpQueue(newDestinationFloor);
    } else {
        addToDownQueue(newDestinationFloor);
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
    std::unique_lock<std::mutex> lock(elevatorMutex);
    stopSignal.store(true);
    elevatorCV.notify_all();
}

void Elevator::waitForElevatorRequest() {

    std::unique_lock<std::mutex> lock(elevatorMutex);

    elevatorCV.wait_for(lock, std::chrono::seconds(10), [&]() {
        return ((upQueue.size() + downQueue.size()) > 0) || stopSignal.load();
    });

    lock.unlock();

    if ((getUpQueueSize() + getDownQueueSize()) == 0 && getCurrentFloorNumber() != 0) {
        addToDownQueue(0);
        setCurrentElevatorState(DEFAULT);
    }
}

void Elevator::setCurrentElevatorState(ElevatorState elevatorState) {
    std::lock_guard<std::mutex> lock(elevatorMutex);
    currentElevatorState = elevatorState;
}

void Elevator::addToUpQueue(int floorNumber) {
    std::lock_guard<std::mutex> lock(elevatorMutex);
    upQueue.insert(floorNumber);
}

void Elevator::addToDownQueue(int floorNumber) {
    std::lock_guard<std::mutex> lock(elevatorMutex);
    downQueue.insert(floorNumber);
}

void Elevator::removeFromUpQueue(int floorNumber) {
    std::lock_guard<std::mutex> lock(elevatorMutex);
    if (upQueue.find(floorNumber) != upQueue.end()) {
        upQueue.erase(upQueue.find(floorNumber));
    }
}

void Elevator::removeFromDownQueue(int floorNumber) {
    std::lock_guard<std::mutex> lock(elevatorMutex);
    if (downQueue.find(floorNumber) != downQueue.end()) {
        downQueue.erase(downQueue.find(floorNumber));
    }
}

bool Elevator::existsInUpQueue(int floorNumber) {
    std::lock_guard<std::mutex> lock(elevatorMutex);
    if (upQueue.find(floorNumber) != upQueue.end()) {
        return true;
    }
    return false;
}

bool Elevator::existsInDownQueue(int floorNumber) {
    std::lock_guard<std::mutex> lock(elevatorMutex);
    if (downQueue.find(floorNumber) != downQueue.end()) {
        return true;
    }
    return false;
}

int Elevator::getUpQueueSize() {
    std::lock_guard<std::mutex> lock(elevatorMutex);
    return upQueue.size();
}

int Elevator::getDownQueueSize() {
    std::lock_guard<std::mutex> lock(elevatorMutex);
    return downQueue.size();
}

Floor& Elevator::getFloorByNumber(int floorNumber) {
    return floors[floorNumber + 2];
}

std::vector<Floor>::iterator& Elevator::getFloorIterator() {
    return currentFloorIterator;
}

std::condition_variable& Elevator::getElevatorCV() {
    return elevatorCV;
}

std::vector<int>& Elevator::getPersonArray() {
    return personsInsideElevator;
}

void Elevator::moveElevatorDown() {
    moveElevator(downQueue);
}

void Elevator::moveElevatorUp() {
    moveElevator(upQueue);
}

Elevator::~Elevator() {
    stopSignal.store(true);
    elevatorCV.notify_all();
}