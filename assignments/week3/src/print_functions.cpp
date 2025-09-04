#include <iostream>
#include "exception_handling.h"
#include "atof_functions.h"
#include "matrix.h"
#include "matrix_operations.h"

bool exitProgram = false;

extern const char* PRINT_RESULT_MATRIX;
extern const char* PRINT_FIRST_MATRIX;
extern const char* PRINT_SECOND_MATRIX;
extern const char* PRINT_MENU;
extern const char* PRINT_PERFORM_ADDITON;
extern const char* PRINT_PERFORM_MULTIPLICATION;
extern const char* PRINT_EXIT_PROGRAM;
extern const char* PRINT_MATRIX_INVALID_INPUT;

void printResultMatrix(Matrix& resultMatrix) {
    std::cout << PRINT_RESULT_MATRIX << std::endl;
    resultMatrix.print();
}

void printInputMatrices(Matrix& firstMatrix, Matrix& secondMatrix) {

    std::cout << PRINT_FIRST_MATRIX << std::endl;
    firstMatrix.print();

    std::cout << PRINT_SECOND_MATRIX << std::endl;
    secondMatrix.print();

}

void printMenu() {

    std::cout << PRINT_MENU << std::endl;
     
}

void printOption(char* input) {

    if (!isValidMenuOption(input)) {
        exitProgram = true;
    }
    switch(input[0]) {
        case '1':
            std::cout << PRINT_PERFORM_ADDITON << std::endl;
            break;

        case '2':
            std::cout << PRINT_PERFORM_MULTIPLICATION << std::endl;
            break;

        default:
            std::cout << PRINT_EXIT_PROGRAM << std::endl;
            break;
    }
}

void performMatrixOperation(const char* input, Matrix& resultMatrix, Matrix& matrixOne, Matrix& matrixTwo) {
    
    switch(input[0]) {
        case '1':
            addTwoMatrices(resultMatrix, matrixOne, matrixTwo);
            break;

        case '2':
            multiplyTwoMatrices(resultMatrix, matrixOne, matrixTwo);
            break;

        default:
            std::cout << PRINT_MATRIX_INVALID_INPUT << std::endl;
            break;
    }

    return;
}