#include <iostream>
#include "constants.h"
#include "matrix.h"
#include "user_option.h"
#include "exception_handling.h"
#include "atof_functions.h"

bool ExceptionHandling::isValidNumber(const char* input) {
    bool result = true;
    int indexOfFirstDecimal = -1;
    if (checkForNegative(input)) {
        input++;
    }
    if (isValidFloatingPoint(input)) {
        indexOfFirstDecimal = Atof::firstDecimalIndex(input);
    }
    int index = 0;
    while (input[index] != '\0') {
        int character = input[index] - '0';
        if (index != indexOfFirstDecimal && (character < 0 || character > 9)) {
            result = false;
        }
        index++;
    }
    return result;
}

bool ExceptionHandling::isValidMatrixInput(char charElement[INTEGER_INPUT]) {
    bool result = true;
    if(handleInputError(10) || !isValidNumber(charElement)) {
        std::cout << PRINT_INVALID_INPUT << std::endl;
        result = false;
    }
    return result;
}

bool ExceptionHandling::handleInputError(int limit) {
    bool result = false;
    if (std::cin.fail()) {
        std::cout << PRINT_INPUT_TOO_LONG << std::endl;
        std::cin.clear();
        std::cin.ignore(IGNORE_INPUT, '\n');
        result = true;
    }
    return result;
}

bool ExceptionHandling::isValidInput(char* input) {
    bool result = true;
    if (checkForNegative(input)) {
        result = false;
    }
    int inputLength = Atof::calculateInputLength(input);
    if (handleInputError(INTEGER_INPUT)) {
        result = false;
    }
    for (int index = 0; index < inputLength; index++) {
        if (input[index] < '1' || input[index] > '9') {
            result = false;
            std::cout << PRINT_MATRIX_INVALID_INPUT << std::endl;
            break;
        }
    }
    return result;
}

bool ExceptionHandling::isValidFloatingPoint(const char* input) {
    int inputLength = Atof::calculateInputLength(input);
    for (int index = 0; index < inputLength - 1; index++) {
        if (input[index] == '.') {
            return true;
        }
    }
    return false;
}

bool ExceptionHandling::checkForNegative(const char* input) {
    if (input[0] == '-') {
        return true;
    }
    return false;
}

bool ExceptionHandling::inputFail() {
    bool result = false;
    if (std::cin.peek() != '\n') {
        std::cout << PRINT_EXIT_PROGRAM << std::endl;
        std::cin.ignore(1000, '\n');
        result = true;
    }
    return result;
}

bool ExceptionHandling::isValidMenuOption(char input) {

    bool result = true;
    if ((input != '1' && input != '2') || input != '\0') {
        result = false;
    }
    return result;
}

