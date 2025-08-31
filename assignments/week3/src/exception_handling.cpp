#include <iostream>
#include "exception_handling.h"
#include "print_functions.h"
#include "matrix.h"
#include "atof_functions.h"

extern const char* PRINT_MATRIX_INVALID_ADDITION;
extern const char* PRINT_MATRIX_INVALID_MULTIPLICATION;
extern const char* PRINT_MATRIX_INVALID_INPUT;
extern const char* PRINT_INPUT_TOO_LONG;

bool handleInputError(int limit) {
    if (std::cin.fail()) {
        std::cout << PRINT_INPUT_TOO_LONG << std::endl;
        std::cin.clear();
        std::cin.ignore(limit, '\n');
        return true;
    }
    return false;
}

bool isValidMatrix(Matrix matrices[2], const char* input) {
    if (input[0] == '1') {
        if (matrices[0].row != matrices[1].row || matrices[0].column != matrices[1].column) {
            std::cout << PRINT_MATRIX_INVALID_ADDITION << std::endl;
            return false;
        }
    } else if (input[0] == '2') {
        if (matrices[0].column != matrices[1].row) {
            std::cout << PRINT_MATRIX_INVALID_MULTIPLICATION << std::endl;
            return false;
        }
    }
    return true;
}

bool isValidNumber(const char* input) {
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
            return false;
        }
        index++;
    }
    return true;
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

bool isValidInput(char* input) {
    int inputLength = calculateInputLength(input);
    if (handleInputError(10)) {
        return false;
    }
    for (int index = 0; index < inputLength; index++) {
        if (input[index] < '0' || input[index] > '9') {
            std::cout << PRINT_MATRIX_INVALID_INPUT << std::endl;
            return false;
        }
    }
    return true;
}

bool isValidMenuOption(char* input) {
    removeWhiteSpaces(input);
    if ((input[0] != '1' && input[0] != '2') || input[1] != '\0') {
        return false;
    }
    return true;
}

bool checkForNegative(const char* input) {
    if (input[0] == '-') {
        return true;
    }
    return false;
}
