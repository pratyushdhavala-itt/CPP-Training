#include "matrix_multiplication.h"
#include "matrix.h"
#include "constants.h"
#include "exception_handling.h"

MultiplicationMatrix::MultiplicationMatrix(Matrix& matrixOne, Matrix& matrixTwo) : 
    Matrix(matrixOne.getRow(), matrixTwo.getColumn()), matrixOne{matrixOne}, matrixTwo{matrixTwo}, validity{true} {
    if(!validMultiplication()) {
        validity = false;
        std::cout << PRINT_DIMENSIONS_MATCH << std::endl;
    } else {
        multiply();
    }
}

void MultiplicationMatrix::multiply() {

    for (int rowIndex = 0; rowIndex < getRow(); rowIndex++) {
        for (int columnIndex = 0; columnIndex < getColumn(); columnIndex++) {
            for (int commonIndex = 0; commonIndex < matrixOne.getColumn(); commonIndex++) {
                *(*(matrixArray + rowIndex) + columnIndex) += matrixOne.getElement(rowIndex, commonIndex) * matrixTwo.getElement(commonIndex, columnIndex);
            }
        }
    }
}

void MultiplicationMatrix::print() const {
    std::cout << PRINT_RESULT_MATRIX << std::endl;
    displayMatrix();
}

bool MultiplicationMatrix::validMultiplication() {
    bool result = ExceptionHandling::validMultiplication(matrixOne, matrixTwo);
    return result;
}
