#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H

#include "ElevatorController.h"

void processElevatorRequest(ElevatorController& elevatorController);
void changeDestinationFloor(ElevatorController& elevatorController);
int inputChoice(int min, int max);
void inputElevatorRequest(ElevatorController& elevatorController);
bool isValidInput(int directionChoice, int sourceFloor, int destinationFloor);

#endif