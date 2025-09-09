#ifndef EXCEPTION_HANDLING_H
#define EXCEPTION_HANDLING_H

#include "matrix.h"
#include "constants.h"
#include "user_option.h"

class ExceptionHandling {

public:

    static bool inputFail();
    
    static bool isValidMenuOption(char input);
    
    static bool canPerformOperation(Matrix& matrixOne, Matrix& matrixTwo, UserOption& userOption);

    static bool validAddition(Matrix& matrixOne, Matrix& matrixTwo);

    static bool validMultiplication(Matrix& matrixOne, Matrix& matrixTwo);

    static bool checkForNegative(const char* input);

    static bool isValidFloatingPoint(const char* input);

    static bool handleInputError(int limit);

    static bool isValidInput(char* input);

    static bool isValidMatrixInput(char charElement[10]);

    static bool isValidNumber(const char* input);
};

#endif
