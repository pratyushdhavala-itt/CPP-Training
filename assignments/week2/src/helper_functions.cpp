#include "../include/helper_functions.h"
#include <iostream>
bool repeatProgramOrNot(const char* input) {
    
    if (input[0] != 'y' && input[0] != 'Y') {
        return false;
    }
    return true;
}

double convertToNumber(const char* input) {
    double result = 0.0;
    if (isValidFloatingPoint(input)) {
        result = convertToFloatingNumber(input);
    } else {
        result = convertToInteger(input);
    }
    return result;
}

int findPreDecimalPointLength(const char* input) {
    int indexOfDecimalPoint = firstDecimalIndex(input);
    int preDecimalPointLength = 0;
    while (preDecimalPointLength != indexOfDecimalPoint) {
        preDecimalPointLength++;
    }
    return preDecimalPointLength;
}

int findPostDecimalPointLength(const char* input) {
    int inputLength = calculateInputLength(input);
    int preDecimalPointLength = findPreDecimalPointLength(input);
    int postDecimalPointLength = inputLength - preDecimalPointLength - 1;
    return postDecimalPointLength;
}

bool isNotANumber(const char* input) {

    int indexOfFirstDecimal = -1;

    if (checkForNegative(input)) {
        input++;
    }

    if (isValidFloatingPoint(input)) {
        indexOfFirstDecimal = firstDecimalIndex(input);
    }
    
    int index = 0;

    while (input[index] != '\0') {
        int character = input[index] - '0';
        if (index != indexOfFirstDecimal && (character < 0 || character > 9)) {
            return true;
        }
        index++;
    }

    return false;
}

int firstDecimalIndex(const char* input) {

    int index = 0;
    while (input[index] != '\0') {
        if (input[index] == '.') {
            return index;
        }
        index++;
    }
    return -1;
}

bool isValidFloatingPoint(const char* input) {

    int inputLength = calculateInputLength(input);
    
    for (int index = 0; index < inputLength - 1; index++) {

        if (input[index] == '.') {
            return true;
        }
    }

    return false;
}

bool checkForNegative(const char* input) {

    if (input[0] == '-') {
        return true;
    }
    return false;
}

int findPower(double base, double exponent) {

    double result = 1.0;
    if (exponent >= 0) {
        for (int numberOfTimesMultiplied = 0; numberOfTimesMultiplied < exponent; numberOfTimesMultiplied++) {
            result *= base;
        }
    } else {
        for (int numberOfTimesMultiplied = exponent; numberOfTimesMultiplied < 0; numberOfTimesMultiplied++) {
            result /= base;
        }
    }
    return result;
}

int calculateInputLength(const char* input) {

    int inputLength = 0;
    while (input[inputLength] != '\0') {
        inputLength++;
    }
    return inputLength;
}

int convertToInteger(const char* input) {

    bool isNegative = false;
    if (checkForNegative(input)) {
        isNegative = true;
        input++;
    }

    double result = 0.0;
    int inputLength = calculateInputLength(input);
    for (int index = 0; index < inputLength; index++) {
        double number = input[index] - '0';
        number = number * findPower(10, inputLength - index - 1);
        result += number;
    }

    if (isNegative) {
        result = result * (-1);
    }
    
    return result;

}

void removeWhiteSpaces(char input[]) {

    int startingIndex = 0;
    while (input[startingIndex] == ' ' || input[startingIndex] == '\n' || input[startingIndex] == '\t') {
        startingIndex++;
    }

    int endingIndex = startingIndex;
    while (input[endingIndex] != '\0') {
        endingIndex++;
    }
    endingIndex--;

    while (endingIndex >= startingIndex && (input[endingIndex] == ' ' || input[endingIndex] == '\n' || input[endingIndex] == '\t')) {
        endingIndex--;
    }

    int newStartingIndex = 0;
    for (int newValue = startingIndex; newValue <= endingIndex; newValue++) {
        input[newStartingIndex] = input[newValue];
        newStartingIndex++;
    }
    input[newStartingIndex] = '\0';
}

double convertToFloatingNumber(const char* input) {

    int preDecimalPointLength = findPreDecimalPointLength(input);
    int postDecimalPointLength = findPostDecimalPointLength(input);
    int inputLength = calculateInputLength(input);

    double result = 0.0;
    bool isBeforeDecimalPoint = true;

    for (int index = 0; index < inputLength; index++) {

        if (input[index] != '.' && isBeforeDecimalPoint) {
            double number = input[index] - '0';
            number = number * findPower(10, preDecimalPointLength - index - 1);
            result += number;
        } else if (input[index] == '.') {
            isBeforeDecimalPoint = false;
        } else {
            double number = input[index] - '0';
            number = number * findPower(10, -(index - preDecimalPointLength));
            result += number;
        }
    }
    return result;
}
