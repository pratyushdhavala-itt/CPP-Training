#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include "ElevatorLogger.h"
#include "Elevator.h"
#include "ElevatorController.h"

void processElevatorRequest(ElevatorController& elevatorController) {

    int directionChoice;
    int sourceFloor;
    int destinationFloor;

    while (true) {
        std::cout << "Press Up/Down:\n   1. Up\n   2. Down\nYour option: ";
        std::cin >> directionChoice;

        std::cout << "Enter your current floor: ";
        std::cin >> sourceFloor;
        
        std::cout << "Enter your destination floor: ";
        std::cin >> destinationFloor;

        elevatorController.addRequestToQueue({(ElevatorRequest::Direction) directionChoice, sourceFloor, destinationFloor});
    }
}

void changeDestinationFloor(ElevatorController& elevatorController) {

    int personId;
    int destinationFloor;

    while (true) {
        std::cout << "Please enter the person ID: ";
        std::cin >> personId;

        std::cout << "Enter the floor you want to change: ";
        std::cin >> destinationFloor;



    }
}

int main() {

    std::mutex* loggerMutex = new std::mutex;
    ElevatorLogger logger;
    Elevator elevatorOne(1, logger, loggerMutex);
    Elevator elevatorTwo(2, logger, loggerMutex);
    ElevatorController elevatorController(elevatorOne, elevatorTwo);

    std::thread t1(&ElevatorController::startElevatorController, &elevatorController);



    t1.join();
    
    return 0;
}
