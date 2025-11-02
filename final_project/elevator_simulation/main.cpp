#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include "ElevatorLogger.h"
#include "Elevator.h"
#include "ElevatorController.h"
#include "utility_functions.h"

int main() {

    ElevatorLogger logger;
    Elevator elevatorOne(1, logger);
    Elevator elevatorTwo(2, logger);
    std::vector<Elevator*> elevators {&elevatorOne, &elevatorTwo};
    ElevatorController elevatorController(elevators);

    std::thread t1(&ElevatorController::runElevatorController, &elevatorController);

    inputElevatorRequest(elevatorController);

    t1.join();
    
    return 0;
}
