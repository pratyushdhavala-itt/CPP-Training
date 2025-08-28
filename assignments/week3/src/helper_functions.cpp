#include <iostream>
#include "helper_functions.h"
using namespace std;

bool isValidMatrix(Matrix matrices[2], const char* input) {
    if (input[0] == '1') {
        if (matrices[0].row != matrices[1].row || matrices[0].column != matrices[1].column) {
            cout << "Matrix dimensions do not match ! ! ! Try again ! ! !" << endl;
            return false;
        }
    } else if (input[0] == '2') {
        if (matrices[0].column != matrices[1].row) {
            cout << "Column of Matrix 1 and Row of Matrix 2 do not match ! ! ! Try again ! ! ! " << endl;
            return false;
        }
    }
    return true;
}


bool exitProgram = false;

void performMatrixOperation(const char* input, Matrix& resultMatrix, Matrix& matrixOne, Matrix& matrixTwo) {
    switch(input[0]) {
        case '1':
            resultMatrix.add(matrixOne, matrixTwo);
            break;

        case '2':
            resultMatrix.multiply(matrixOne, matrixTwo);
            break;

        default:
            cout << "Wrong input ! ! ! Try again ! ! ! " << endl;
            break;
    }

    return;
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




bool isValidRowOrColumn(char* input) {

    int inputLength = calculateInputLength(input);

    if (inputFail(10)) {

        return false;
    }

    for (int index = 0; index < inputLength; index++) {
        if (input[index] < '0' || input[index] > '9') {
            cout << "Wrong input ! ! ! Try again ! ! !" << endl;
            return false;
        }
    }
    return true;
}

void printChosenOption(char* input) {

    if (!isValidMenuOption(input)) {
        exitProgram = true;
    }
    switch(input[0]) {
        case '1':
            cout << "Performing Matrix Addition" << endl;
            break;

        case '2':
            cout << "Performing Matrix Multiplication" << endl;
            break;

        default:
            cout << "Exited program successfully ! ! ! " << endl;
            break;
    }
}

bool isValidMenuOption(char* input) {

    removeWhiteSpaces(input);

    if ((input[0] != '1' && input[0] != '2') || input[1] != '\0') {
        return false;
    }
    return true;
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

bool checkForNegative(const char* input) {

    if (input[0] == '-') {
        return true;
    }
    return false;
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

bool inputFail(int limit) {
    if (cin.fail()) {
        cout << "Oops ! ! ! Your input is too long ! ! !" << endl;
        cin.clear();
        cin.ignore(limit, '\n');
        return true;
    }
    return false;
}

void printMenu() {

    cout << "Please enter the option from the below list:-" << '\n'
         << "1. Addition" << '\n' 
         << "2. Multipliction" << '\n'
         << "Any other key to exit." <<
    endl;
     
}
