#include <iostream>
#include "matrix_addition.h"
#include "constants.h"
#include "exception_handling.h"

AdditionMatrix::AdditionMatrix(Matrix& matrixOne, Matrix& matrixTwo)
: Matrix(matrixOne.getRow(), matrixOne.getColumn()), matrixOne{matrixOne}, matrixTwo{matrixTwo} , validity{true} {
    if (!validAddition()) {
        validity = false;
        std::cout << PRINT_DIMENSIONS_MATCH << std::endl;
    } else {
        init();
        add();
    }
}

void AdditionMatrix::add() {
    
    for (int rowIndex = 0; rowIndex < matrixRow; rowIndex++) {
        for (int columnIndex = 0; columnIndex < matrixColumn; columnIndex++) {
            *(*(matrixArray + rowIndex) + columnIndex) = matrixOne.getElement(rowIndex, columnIndex) + matrixTwo.getElement(rowIndex, columnIndex);
        }
    }
}

void AdditionMatrix::print() const {
    std::cout << PRINT_RESULT_MATRIX << std::endl;
    displayMatrix();
}

bool AdditionMatrix::validAddition() {
    bool result = ExceptionHandling::validAddition(matrixOne, matrixTwo);
    return result;
}