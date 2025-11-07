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
    std::string prettyString;
    std::string elevatorTitle;
    std::string elevatorOneLog;
    std::string elevatorTwoLog;
    std::vector<std::string> elevatorOneLogs;
    std::vector<std::string> elevatorTwoLogs;

public:
    ElevatorLogger();
    virtual void operator()(int elevatorId, int currentFloor, std::string content);
    virtual void filterAndInsertLogs(std::string content);
    virtual void convertToStructuredString();
    std::vector<std::string>& getElevatorOneLogs();
    std::vector<std::string>& getElevatorTwoLogs();
    int& getMaxLogSize();
    std::string& getPrettyString();
    int& getElevatorOneCurrentFloor();
    int& getElevatorTwoCurrentFloor();
};

#endif