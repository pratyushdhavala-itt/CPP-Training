#include "../include/helper_functions.h"
#include "../include/math_operations.h"
#include <iostream>

extern "C" {

    const char* PRINT_ENTER_FIRST_NUMBER = "Please enter the first number: ";
    const char* PRINT_ENTER_SECOND_NUMBER = "Please enter the second number: ";
    const char* PRINT_WRONG_INPUT = "Wrong input ! ! !";
    const char* PRINT_REPEAT_STRING = "Do you want to continue? (y/Y). Enter any other key to exit.";
    const char* PRINT_RESULT = "Result: ";

}

// void checkInputSize(const char* input) {
    
// }

void printMenu() {

    std::cout << "Please enter the option from the below list:" << '\n' <<
                     "1. Addition" << '\n' <<
                     "2. Subtraction" << '\n' <<
                     "3. Multiplication" << '\n' <<
                     "4. Division" << '\n' <<
                     "5. Exit Program" <<
    std::endl;

}

bool isValidMenuOption(char* input) {

    removeWhiteSpaces(input);

    if (isValidNumber(input) && isValidFloatingPoint(input)) {
        std::cout << "Not a valid input ! ! !" << std::endl;
        return false;
    }
    return true;
}

bool printChosenOption(const char* input) {

    int choice = convertToInteger(input);
    bool exitProgram = false;

    switch(choice) {
        case 1:
            std::cout << "Performing addition of two numbers: " << std::endl;
            break;
        
        case 2:
            std::cout << "Performing subtraction of two numbers: " << std::endl;
            break;

        case 3:
            std::cout << "Performing multiplication of two numbers: " << std::endl;
            break;
            
        case 4:
            std::cout << "Performing division of two numbers: " << std::endl;
            break;
            
        case 5:
            std::cout << "Exiting the program ! ! !" << std::endl;
            exitProgram = true;
            break;

        default: 
            std::cout << "Please input an option from 1 to 5" << std::endl;
            exitProgram = true;
    }
    return exitProgram;
}

double performChosenOperation(char* firstNumberChar, char* secondNumberChar, const char* input) {
    
    int choice = convertToInteger(input);

    double firstNumber = convertToNumber(firstNumberChar);
    double secondNumber = convertToNumber(secondNumberChar);

    double result = 0.0;
    switch(choice) {
        case 1:
            result = addTwoNumbers(firstNumber, secondNumber);
            break;
            
        case 2:
            result = subtractTwoNumbers(firstNumber, secondNumber);
            break;

        case 3:
            result = multiplyTwoNumbers(firstNumber, secondNumber);
            break;

        case 4:
            result = divideTwoNumbers(firstNumber, secondNumber);
            break;
    }
    return result;
}

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

double findPower(double base, double exponent) {

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

void removeWhiteSpaces(char* input) {

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
