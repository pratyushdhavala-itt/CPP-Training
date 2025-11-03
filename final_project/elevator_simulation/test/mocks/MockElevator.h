#ifndef MOCK_ELEVATOR_H
#define MOCK_ELEVATOR_H

#include <gmock/gmock.h>
#include "Elevator.h"

class MockElevator : public Elevator {
  
public:
    MockElevator(int id, ElevatorLogger& logger) : Elevator(id, logger) {} 
    MOCK_METHOD(ElevatorState, getElevatorState, (), (override));
    MOCK_METHOD(int, getCurrentFloorNumber, (), (override));
    MOCK_METHOD(int, pendingRequests, (), (override));
    MOCK_METHOD(void, processElevatorRequest, (const ElevatorRequest& request), (override));
    MOCK_METHOD(bool, personExistsInsideElevator, (int personId), (override));
    MOCK_METHOD(void, changePersonDestinationFloor, (int personId, int newDestinationFloor), (override));
    MOCK_METHOD(void, stopElevator, (), (override));
    MOCK_METHOD(void, addPersonActionToFloor, (int floorNumber, int personId, Floor::PersonAction action), (override));
    MOCK_METHOD(void, setCurrentElevatorState, (ElevatorState elevatorState), (override));
    MOCK_METHOD(void, addToUpQueue, (int floorNumber), (override));
    MOCK_METHOD(void, addToDownQueue, (int floorNumber), (override));
    MOCK_METHOD(void, removeFromUpQueue, (int floorNumber), (override));
    MOCK_METHOD(void, removeFromDownQueue, (int floorNumber), (override));
    MOCK_METHOD(bool, existsInUpQueue, (int floorNumber), (override));
    MOCK_METHOD(bool, existsInDownQueue, (int floorNumber), (override));
    MOCK_METHOD(int, getUpQueueSize, (), (override));
    MOCK_METHOD(int, getDownQueueSize, (), (override));
    MOCK_METHOD(void, waitForElevatorRequest, (), (override));
    MOCK_METHOD(void, moveElevatorDown, (), (override));
    MOCK_METHOD(void, moveElevatorUp, (), (override));

};

#endif
