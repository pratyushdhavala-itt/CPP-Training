#include "ElevatorLogger.h"

ElevatorLogger::ElevatorLogger() : elevatorOneCurrentFloor{0}, elevatorTwoCurrentFloor{0}, maxLogSize{0}, filename{"output.txt"} {
    std::ostringstream oss;
    oss << std::left << std::setw(45) << "ELEVATOR 1" << " | " << "ELEVATOR 2" << "\n";
    elevatorTitle = oss.str();
}

void ElevatorLogger::operator()(int elevatorId, int currentFloor, std::string content) {
    std::ostringstream oss;
    if (elevatorId == 1) {
        elevatorOneCurrentFloor = currentFloor;
    } else {
        elevatorTwoCurrentFloor = currentFloor;
    }
    oss << std::left << std::setw(45) << "FLOOR: " + std::to_string(elevatorOneCurrentFloor) << " | " << "FLOOR: " + std::to_string(elevatorTwoCurrentFloor) << "\n";
    std::string currentFloorString = oss.str();
    std::fstream file;
    file.open(filename, std::ios::out);
    elevatorLogs += content;
    filterAndInsertLogs(content);
    convertToStructuredString();
    std::string finalString = elevatorTitle + currentFloorString + prettyString;
    {
        std::unique_lock lock(loggerMutex);
        file << finalString;
    }
    file.close();
}

void ElevatorLogger::filterAndInsertLogs(std::string content) {
    if (content.find("[ELEVATOR 1]") != std::string::npos) {
        elevatorOneLogs.push_back(content.substr(content.find("]: ") + 3));
    } else if (content.find("[ELEVATOR 2]") != std::string::npos) {
        elevatorTwoLogs.push_back(content.substr(content.find("]: ") + 3));
    }
    maxLogSize++;
}

void ElevatorLogger::convertToStructuredString() {
    elevatorOneLogs.resize(maxLogSize, "");
    elevatorTwoLogs.resize(maxLogSize, "");
    std::ostringstream oss;
    oss << std::left << std::setw(45) << elevatorOneLogs[maxLogSize - 1] << " | " << elevatorTwoLogs[maxLogSize - 1] << "\n";
    prettyString += oss.str();
    oss.clear();
}