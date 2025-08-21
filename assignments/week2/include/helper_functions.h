#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

extern "C" {

void removeWhiteSpaces(char input[]);
int findPower(double base, double exponent);
int calculateInputLength(const char* input);
int convertToInteger(const char* input);
bool isNotANumber(const char* input);
int firstDecimalIndex(const char* input);
bool isValidFloatingPoint(const char* input);
bool checkForNegative(const char* input);
int findPreDecimalPointLength(const char* input);
int findPostDecimalPointLength(const char* input);
double convertToNumber(const char* input);
bool repeatProgramOrNot(const char* input);
double convertToFloatingNumber(const char* input);

}

#endif