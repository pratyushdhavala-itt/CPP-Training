#include <iostream>
#include "constants.h"
#include "matrix.h"
#include "option.h"
#include "exception_handling.h"
#include "atof.h"

namespace ExceptionHandling {

    bool isValidNumber(const char* input) {
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
                return false;
            }
            index++;
        }
        return true;
    }

    bool isValidMatrixInput(char charElement[10]) {
        if(handleInputError(10) || !isValidNumber(charElement)) {
            std::cout << PRINT_INVALID_INPUT << std::endl;
            return false;
        }
        return true;
    }

    bool handleInputError(int limit) {
        if (std::cin.fail()) {
            std::cout << PRINT_INPUT_TOO_LONG << std::endl;
            std::cin.clear();
            std::cin.ignore(limit, '\n');
            return true;
        }
        return false;
    }

    bool isValidInput(char* input) {
        int inputLength = Atof::calculateInputLength(input);
        if (handleInputError(10)) {
            return false;
        }
        for (int index = 0; index < inputLength; index++) {
            if (input[index] < '1' || input[index] > '9') {
                std::cout << PRINT_MATRIX_INVALID_INPUT << std::endl;
                return false;
            }
        }
        return true;
    }
    
    bool isValidFloatingPoint(const char* input) {
        int inputLength = Atof::calculateInputLength(input);
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
    bool inputFail() {
        bool result = false;
        if (std::cin.peek() != '\n') {
            std::cout << PRINT_EXIT_PROGRAM << std::endl;
            std::cin.ignore(1000, '\n');
            result = true;
        }
        return result;
    }

    bool isValidMenuOption(char input) {

        bool result = true;
        if ((input != '1' && input != '2') || input != '\0') {
            result = false;
        }
        return result;
    }

    bool isCompatible(Matrix& matrixOne, Matrix& matrixTwo, Option& option) {
        bool result = true;
        if (option.getOperation() == Option::ADDITION) {
            result = validAddition(matrixOne, matrixTwo);
        } else if (option.getOperation() == Option::MULTIPLICATION) {
            result = validMultiplication(matrixOne, matrixTwo);
        }
        if (!result) {
            std::cout << "Dimensions do not match ! ! ! Try again ! ! !" << std::endl;
        }
        return result;
    }

    bool validAddition(Matrix& matrixOne, Matrix& matrixTwo) {
        bool result = true;
        if (matrixOne.getRow() != matrixTwo.getRow() || matrixOne.getColumn() != matrixTwo.getColumn()) {
            result = false;
        }
        return result;
    }

    bool validMultiplication(Matrix& matrixOne, Matrix& matrixTwo) {
        bool result = true;
        if (matrixOne.getColumn() != matrixTwo.getRow()) {
            return false;
        }
        return result;
    }

};