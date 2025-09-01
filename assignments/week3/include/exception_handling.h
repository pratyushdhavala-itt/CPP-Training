#ifndef EXCEPTION_HANDLING
#define EXCEPTION_HANDLING

#include "matrix.h"
bool handleInputError(int limit);
bool isValidMatrix(Matrix matrices[2], const char* input);
bool isValidNumber(const char* input);
bool isValidFloatingPoint(const char* input);
bool isValidInput(char* input, int& matrixIndex);
bool isValidMenuOption(char* input);
bool checkForNegative(const char* input);
bool isValidMatrixInput(char charElement[10], int& columnIndex);

#endif