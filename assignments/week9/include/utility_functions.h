#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Lane.h"
#include "constants.h"

extern bool allCarsPassed;

void addMoreCars(std::vector<Lane*>& lanes);
void inputNumberOfCarsPerLane(std::vector<Lane*>& lanes, std::mutex* printMtx);
int inputChoice(int minChoice, int maxChoice, bool exit);

#endif