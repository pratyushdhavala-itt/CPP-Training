double substractTwoNumbers(double firstNumber, double secondNumber) {
    
    double result;

    if (firstNumber >= secondNumber) {
        result = firstNumber - secondNumber;
    } else {
        result = secondNumber - firstNumber;
    }

    return result;
}