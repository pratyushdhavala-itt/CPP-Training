#include "utility_functions.h"

void addMoreCars(std::vector<Lane*>& lanes) {
    int laneNumber;
    int numberOfCarsToBeAdded;
    while (true) {
        std::cout << PRINT_ENTER_LANE_NUMBER;
        laneNumber = inputChoice(1, lanes.size(), true);
        if (laneNumber == -1) {
            allCarsPassed = true;
            std::cout << PRINT_END_PROGRAM_AFTER_CROSSING << std::endl;
            break;
        }
        std::cout << PRINT_ENTER_CARS_TO_BE_ADDED;
        numberOfCarsToBeAdded = inputChoice(1, 99, false);
        auto it = std::find_if(lanes.begin(), lanes.end(), [&laneNumber](Lane* lane) {
            return lane->getId() == laneNumber;
        });
        (*it)->addCars(numberOfCarsToBeAdded);
    }
}

void inputNumberOfCarsPerLane(std::vector<Lane*>& lanes, std::mutex* printMtx) {
    int numberOfCarsPerLane;
    for (int i = 0; i < lanes.capacity(); i++) {
        std::cout << PRINT_ENTER_NUMBER_OF_CARS << i + 1 << PRINT_COLON;
        numberOfCarsPerLane = inputChoice(1, 99, false);
        lanes.push_back(new Lane(i + 1, numberOfCarsPerLane, new TrafficSignal(), printMtx));
    }
}

int inputChoice(int minChoice, int maxChoice, bool exit) {
    char c[3];
    double choice;
    while (true) {
        std::cin.getline(c, 3);
        if (std::cin.fail()) {
            std::cout << PRINT_INVALID_INPUT_ONE;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
        choice = atof(c);
        if (exit) {
            if (choice == -1) return -1;
        }
        if (choice < minChoice || choice > maxChoice || std::floor(choice) != choice) {
            std::cout << PRINT_INVALID_INPUT_TWO;
            continue;
        }
        break;
    }
    return choice;
}