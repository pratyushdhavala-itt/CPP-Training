#include "../include/subtraction.h"

double subtractTwoNumbers(double firstNumber, double secondNumber) {
    
    double result;

    if (firstNumber >= secondNumber) {
        result = firstNumber - secondNumber;
    } else {
        result = secondNumber - firstNumber;
    }

    return result;
}