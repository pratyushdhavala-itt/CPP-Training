#ifndef HELPER_H
#define HELPER_H
#include "matrix.h"

bool isValidMatrix(Matrix matrices[2], const char* input);
void printMenu();
bool inputFail(int limit);
void printChosenOption(char* input);
bool isValidMenuOption(char* input);
void removeWhiteSpaces(char* input);
double findPower(double base, double exponent);
int calculateInputLength(const char* input);
bool checkForNegative(const char* input);
int convertToInteger(const char* input);
bool isValidRowOrColumn(char* input);
double convertToNumber(const char* input);
bool isValidNumber(const char* input);
int firstDecimalIndex(const char* input);
bool isValidFloatingPoint(const char* input);
double convertToFloatingNumber(const char* input);
int findPreDecimalPointLength(const char* input);
int findPostDecimalPointLength(const char* input);
void performMatrixOperation(const char* input, Matrix& resultMatrix, Matrix& matrixOne, Matrix& matrixTwo);

#endif