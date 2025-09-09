#include <iostream>
#include "user_option.h"
#include "matrix.h"
#include "matrix_operation.h"
#include "constants.h"
#include "exception_handling.h"

MatrixOperation::MatrixOperation(Matrix& matrixOne, Matrix& matrixTwo) 
    : matrixOne{matrixOne}, 
      matrixTwo{matrixTwo}, 
      result{matrixOne.matrixRow, matrixTwo.matrixColumn} {

}

void MatrixOperation::multiply() {

    for (int rowIndex = 0; rowIndex < matrixOne.matrixRow; rowIndex++) {
        for (int columnIndex = 0; columnIndex < matrixTwo.matrixColumn; columnIndex++) {
            for (int commonIndex = 0; commonIndex < matrixOne.matrixColumn; commonIndex++) {
                *(*(result.matrixArray + rowIndex) + columnIndex) += matrixOne.getElement(rowIndex, commonIndex) * matrixTwo.getElement(commonIndex, columnIndex);
            }
        }
    }
}

bool MatrixOperation::validMultiplication() {
    bool result = ExceptionHandling::validMultiplication(matrixOne, matrixTwo);
    return result;
}

bool MatrixOperation::validAddition() {
    bool result = ExceptionHandling::validAddition(matrixOne, matrixTwo);
    return result;
}

void MatrixOperation::add() {
    
    for (int rowIndex = 0; rowIndex < matrixOne.matrixRow; rowIndex++) {
        for (int columnIndex = 0; columnIndex < matrixOne.matrixColumn; columnIndex++) {
            *(*(result.matrixArray + rowIndex) + columnIndex) = matrixOne.getElement(rowIndex, columnIndex) + matrixTwo.getElement(rowIndex, columnIndex);
        }
    }
}

void MatrixOperation::performOperation(UserOption& userOption) {

    switch(userOption.getOperation()) {
        case UserOption::ADDITION: {
            if (!validAddition()) {
                break;
            }
            add();
            result.print();
            break;
        }
        case UserOption::MULTIPLICATION: {
            if (!validMultiplication()) {
                break;
            }
            multiply();
            result.print();
            break;
        }
    }
    std::cout << PRINT_PERFORM_AGAIN << std::endl;
}

void MatrixOperation::performAnotherOperation() {

    std::cin.ignore(IGNORE_INPUT, '\n');
    UserOption userOption;
    std::cin >> userOption;

    performOperation(userOption);

}
