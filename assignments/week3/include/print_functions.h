#ifndef PRINT_FUNCTIONS
#define PRINT_FUNCTIONS

#include "matrix.h"

void performMatrixOperation(const char* input, Matrix& resultMatrix, Matrix& matrixOne, Matrix& matrixTwo);
void printOption(char* input);
void printMenu();
void printInputMatrices(Matrix& firstMatrix, Matrix& secondMatrix);
void printResultMatrix(Matrix& resultMatrix);

#endif