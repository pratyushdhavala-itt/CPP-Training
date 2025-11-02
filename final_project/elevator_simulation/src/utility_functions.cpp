#include <iostream>
#include <cmath>
#include "utility_functions.h"
#include "ElevatorController.h"
#include "ElevatorException.h"

void processElevatorRequest(ElevatorController& elevatorController) {
    int directionChoice;
    int sourceFloor;
    int destinationFloor;
    while (true) {

        std::cout << "Enter your current floor: ";
        sourceFloor = inputChoice(-2, 8);

        std::cout << "Enter your destination floor: ";
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
    std::cout << "Please enter the person ID: ";
    personId = inputChoice(1, ElevatorRequest::totalPersonCount);
    std::cout << "Enter the floor you want to change: ";
    destinationFloor = inputChoice(-2, 8);
    try {
        elevatorController.changeDestinationFloor(personId, destinationFloor);
    } catch (const ElevatorException& e) {
        std::cout << e.what() << std::endl;
    }
}
void inputElevatorRequest(ElevatorController& elevatorController) {
    while (true) {
        std::cout << "User Menu: \n   1. Travel in the elevator\n   2. Change destination floor\n   3. Exit\nYour option: ";
        int choice = inputChoice(1, 3);
        switch (choice) {
            case 1: 
                processElevatorRequest(elevatorController);
                break;
            case 2:
                changeDestinationFloor(elevatorController);
                break;
            case 3:
                std::cout << "Exiting elevator simulation ! ! !" << std::endl;
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
            std::cout << "Input is too long or invalid\nTry again: ";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        choice = atof(c);

        if (choice < min || choice > max || std::floor(choice) != choice) {
            std::cout << "Input value is too large or small\nTry again: ";
            continue;
        }
        break;
    }
    return choice;
}