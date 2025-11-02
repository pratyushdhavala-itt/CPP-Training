#ifndef ELEVATOR_LOGGER_H
#define ELEVATOR_LOGGER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <mutex>

class ElevatorLogger {

private:
    std::mutex loggerMutex;
    std::string filename;;
    int elevatorOneCurrentFloor;
    int elevatorTwoCurrentFloor;
    int maxLogSize;
    std::string elevatorLogs;
    std::string prettyString;
    std::string elevatorTitle;
    std::vector<std::string> elevatorOneLogs;
    std::vector<std::string> elevatorTwoLogs;

public:
    ElevatorLogger();
    void operator()(int elevatorId, int currentFloor, std::string content);
    void filterAndInsertLogs(std::string content);
    void convertToStructuredString();
};

#endif