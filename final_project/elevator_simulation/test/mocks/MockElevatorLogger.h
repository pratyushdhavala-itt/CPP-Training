#ifndef MOCK_LOGGER_H
#define MOCK_LOGGER_H

#include <gmock/gmock.h>
#include <string>
#include "ElevatorLogger.h"

class MockElevatorLogger : public ElevatorLogger {
public:
    MOCK_METHOD(void, call, (int elevatorId, int floor, const std::string& message));

    void operator()(int elevatorId, int floor, std::string message) override {
        call(elevatorId, floor, message);
    }
};

#endif
