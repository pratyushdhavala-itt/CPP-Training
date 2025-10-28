#ifndef ELEVATOR_LOGGER_H
#define ELEVATOR_LOGGER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

class ElevatorLogger {

private:
    std::string filename;;
    int elevatorOneCurrentFloor;
    int elevatorTwoCurrentFloor;
    int maxLogSize;
    std::string elevatorLogs;
    std::string prettyString;
    std::vector<std::string> elevatorOneLogs;
    std::vector<std::string> elevatorTwoLogs;

public:

    ElevatorLogger() : elevatorOneCurrentFloor{0}, elevatorTwoCurrentFloor{0}, maxLogSize{0}, filename{"output.txt"} {
        std::ostringstream oss;
        oss << std::left << std::setw(45) << "ELEVATOR 1" << " | " << "ELEVATOR 2" << "\n";
        prettyString = oss.str();
    }

    void operator()(std::string content) {

        std::fstream file;
        file.open(filename, std::ios::out);
        elevatorLogs += content;
        sortAndInsertLogs(content);
        convertToStructuredString();
        file << prettyString;
        file.close();
    }

    void sortAndInsertLogs(std::string content) {

        if (content.find("[ELEVATOR 1]") != std::string::npos) {
            elevatorOneLogs.push_back(content.substr(content.find("]: ") + 3));
        } else if (content.find("[ELEVATOR 2]") != std::string::npos) {
            // std::cout << "PUSHED IN TWO" << std::endl;
            elevatorTwoLogs.push_back(content.substr(content.find("]: ") + 3));
        }
        maxLogSize++;
    }

    void convertToStructuredString() {

        elevatorOneLogs.resize(maxLogSize, "");
        elevatorTwoLogs.resize(maxLogSize, "");

        std::ostringstream oss;
        oss << std::left << std::setw(45) << elevatorOneLogs[maxLogSize - 1] << " | " << elevatorTwoLogs[maxLogSize - 1] << "\n";
        prettyString += oss.str();
        oss.clear();
    }
};

#endif