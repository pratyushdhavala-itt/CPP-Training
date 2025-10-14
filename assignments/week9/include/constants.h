#ifndef CONSTANTS_H
#define CONSTANTS_H

inline bool exitProgram = false;

inline const char* PRINT_ENTER_NUMBER_OF_LANES = "\nEnter number of lanes: ";
inline const char* PRINT_ENTER_NUMBER_OF_CARS = "\nEnter number of cars in lane ";
inline const char* PRINT_COLON = ": ";
inline const char* PRINT_GREEN_LIGHT = "          GREEN LIGHT          ";
inline const char* PRINT_LANE = "LANE: ";
inline const char* PRINT_LINE_SEPARATOR = "\n----------------------------------------------\n"; 
inline const char* PRINT_RED_LIGHT = "          RED LIGHT          ";
inline const char* PRINT_CAR = "Car ";
inline const char* PRINT_CAR_LANE = " from Lane ";
inline const char* PRINT_PASSING = " passing...";
inline const char* PRINT_WELCOME = "Welcome to Traffic Light System Simulation\nInstructions:-\n   1. You can enter the number of cars to be added to a specific lane.\n   2. If you want to end the simulation, enter (-1) in the lane input, the simulation will be stopped after all the cars have passed.";
inline const char* PRINT_ENTER_LANE_NUMBER = "Enter the lane number for more cars to be added to or enter (-1) to exit after all cars pass: ";
inline const char* PRINT_END_PROGRAM_AFTER_CROSSING = "Program will end after all the cars have crossed the signal ! ! !";
inline const char* PRINT_ENTER_CARS_TO_BE_ADDED = "Enter the number of cars to be added: ";
inline const char* PRINT_INVALID_INPUT_ONE = "\nInvalid input ! ! !\nTry again: ";
inline const char* PRINT_INVALID_INPUT_TWO = "\nInput value is too big or small or it is a decimal\nTry again: ";

#endif