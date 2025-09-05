#include "matrix.h"
#include "option.h"

namespace ExceptionHandling {
    
    bool inputFail();
    bool isValidMenuOption(char input);
    
    bool isCompatible(Matrix& matrixOne, Matrix& matrixTwo, Option& option);

    bool validAddition(Matrix& matrixOne, Matrix& matrixTwo);

    bool validMultiplication(Matrix& matrixOne, Matrix& matrixTwo);

    bool checkForNegative(const char* input);

    bool isValidFloatingPoint(const char* input);

    bool handleInputError(int limit);

    bool isValidInput(char* input);

    bool isValidMatrixInput(char charElement[10]);

    bool isValidNumber(const char* input);
};