#ifndef MOCK_ELEVATOR_CONTROLLER_H
#define MOCK_ELEVATOR_CONTROLLER_H

#include <gmock/gmock.h>
#include "ElevatorController.h"

class MockElevatorController : public ElevatorController {
public:
    MockElevatorController(std::vector<Elevator*>& elevators) : ElevatorController(elevators) {}

    MOCK_METHOD(bool, canAssignRequestToElevator, (Elevator& elevator, const ElevatorRequest& request), (override));
    MOCK_METHOD(int, calculateScore, (Elevator& elevator, const ElevatorRequest& request), (override));
    MOCK_METHOD(void, delayRequest, (const ElevatorRequest& request), (override));
};

#endif
