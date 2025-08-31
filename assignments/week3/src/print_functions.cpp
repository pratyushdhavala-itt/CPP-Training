#include <iostream>
#include "exception_handling.h"
#include "atof_functions.h"
#include "matrix.h"

bool exitProgram = false;

void printMenu() {

    std::cout << "Please enter the option from the below list:-" << '\n'
         << "1. Addition" << '\n' 
         << "2. Multipliction" << '\n'
         << "Any other key to exit." <<
    std::endl;
     
}

void printOption(char* input) {

    if (!isValidMenuOption(input)) {
        exitProgram = true;
    }
    switch(input[0]) {
        case '1':
            std::cout << "Performing Matrix Addition" << std::endl;
            break;

        case '2':
            std::cout << "Performing Matrix Multiplication" << std::endl;
            break;

        default:
            std::cout << "Exited program successfully ! ! ! " << std::endl;
            break;
    }
}

void performMatrixOperation(const char* input, Matrix& resultMatrix, Matrix& matrixOne, Matrix& matrixTwo) {
    switch(input[0]) {
        case '1':
            resultMatrix.add(matrixOne, matrixTwo);
            break;

        case '2':
            resultMatrix.multiply(matrixOne, matrixTwo);
            break;

        default:
            std::cout << "Wrong input ! ! ! Try again ! ! ! " << std::endl;
            break;
    }

    return;
}