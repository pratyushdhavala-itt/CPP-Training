#include <iostream>
#include <cmath>
#include "utility_functions.h"
#include "ElevatorController.h"
#include "ElevatorException.h"
#include "constants.h"

void processElevatorRequest(ElevatorController& elevatorController) {
    int directionChoice;
    int sourceFloor;
    int destinationFloor;
    while (true) {

        std::cout << PRINT_ENTER_CURRENT_FLOOR;
        sourceFloor = inputChoice(-2, 8);

        std::cout << PRINT_ENTER_DESTINATION_FLOOR;
        destinationFloor = inputChoice(-2, 8);

        break;
    }
    if (sourceFloor <= destinationFloor) {
        elevatorController.addRequestToQueue({ElevatorRequest::UP, sourceFloor, destinationFloor});
    } else {
        elevatorController.addRequestToQueue({ElevatorRequest::DOWN, sourceFloor, destinationFloor});   
    }
}

void changeDestinationFloor(ElevatorController& elevatorController) {
    int personId;
    int destinationFloor;
    std::cout << PRINT_ENTER_PERSON_ID;
    personId = inputChoice(1, ElevatorRequest::totalPersonCount);
    std::cout << PRINT_ENTER_NEW_DESTINATION_FLOOR;
    destinationFloor = inputChoice(-2, 8);
    try {
        elevatorController.changeDestinationFloor(personId, destinationFloor);
    } catch (const ElevatorException& e) {
        std::cout << e.what() << std::endl;
    }
}
void inputElevatorRequest(ElevatorController& elevatorController) {
    while (true) {
        std::cout << PRINT_ENTER_USER_MENU;
        int choice = inputChoice(1, 3);
        switch (choice) {
            case 1: 
                processElevatorRequest(elevatorController);
                break;
            case 2:
                changeDestinationFloor(elevatorController);
                break;
            case 3:
                std::cout << PRINT_EXIT_SIMULATION << std::endl;
                elevatorController.stopElevatorController();
                return;
        }
    }
}

int inputChoice(int min, int max) {
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

        if (choice < min || choice > max || std::floor(choice) != choice) {
            std::cout << PRINT_INVALID_INPUT_TWO;
            continue;
        }
        break;
    }
    return choice;
}