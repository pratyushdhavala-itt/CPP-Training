#include "ElevatorLogger.h"
#include "constants.h"

ElevatorLogger::ElevatorLogger() : elevatorOneCurrentFloor{0}, elevatorTwoCurrentFloor{0}, maxLogSize{0}, filename{"output.txt"} {
    std::ostringstream oss;
    std::string tempString;
    std::fstream file;
    file.open(filename, std::ios::out);
    oss << std::left << std::setw(45) << PRINT_ELEVATOR_ONE_TITLE << PRINT_SEPARATOR << PRINT_ELEVATOR_TWO_TITLE << "\n";
    elevatorTitle = oss.str();
    file << elevatorTitle;
    oss.str("");
    oss << std::left << std::setw(45) << PRINT_FLOOR_TITLE + std::to_string(elevatorOneCurrentFloor) << PRINT_SEPARATOR << PRINT_FLOOR_TITLE + std::to_string(elevatorTwoCurrentFloor) << "\n";    
    tempString = oss.str();
    file << tempString;
    tempString.clear();
    file.close();
}

void ElevatorLogger::operator()(int elevatorId, int currentFloor, std::string content) {
    std::ostringstream oss;
    if (elevatorId == 1) {
        elevatorOneCurrentFloor = currentFloor;
    } else {
        elevatorTwoCurrentFloor = currentFloor;
    }
    oss << std::left << std::setw(45) << PRINT_FLOOR_TITLE + std::to_string(elevatorOneCurrentFloor) << PRINT_SEPARATOR << PRINT_FLOOR_TITLE + std::to_string(elevatorTwoCurrentFloor) << "\n";
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
    if (content.find(PRINT_ELEVATOR_ONE_LOG) != std::string::npos) {
        elevatorOneLogs.push_back(content.substr(content.find("]: ") + 3));
    } else if (content.find(PRINT_ELEVATOR_TWO_LOG) != std::string::npos) {
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

std::vector<std::string>& ElevatorLogger::getElevatorOneLogs() {
    return elevatorOneLogs;
}
std::vector<std::string>& ElevatorLogger::getElevatorTwoLogs() {
    return elevatorTwoLogs;
}

int& ElevatorLogger::getMaxLogSize() {
    return maxLogSize;
}

std::string& ElevatorLogger::getPrettyString() {
    return prettyString;
}

int& ElevatorLogger::getElevatorOneCurrentFloor() {
    return elevatorOneCurrentFloor;
}
int& ElevatorLogger::getElevatorTwoCurrentFloor() {
    return elevatorTwoCurrentFloor;
}