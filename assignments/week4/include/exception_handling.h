#ifndef EXCEPTION_HANDLING_H
#define EXCEPTION_HANDLING_H

#include "matrix.h"
#include "constants.h"
#include "user_option.h"

namespace ExceptionHandling {
    
    bool inputFail();
    
    bool isValidMenuOption(char input);
    
    bool canPerformOperation(Matrix& matrixOne, Matrix& matrixTwo, UserOption& userOption);

    bool validAddition(Matrix& matrixOne, Matrix& matrixTwo);

    bool validMultiplication(Matrix& matrixOne, Matrix& matrixTwo);

    bool checkForNegative(const char* input);

    bool isValidFloatingPoint(const char* input);

    bool handleInputError(int limit);

    bool isValidInput(char* input);

    bool isValidMatrixInput(char charElement[10]);

    bool isValidNumber(const char* input);
};

#endif
