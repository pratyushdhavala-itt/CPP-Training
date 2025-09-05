#include "multiplication_matrix.h"
#include "matrix.h"
#include "constants.h"

MultiplicationMatrix::MultiplicationMatrix(Matrix& matrixOne, Matrix& matrixTwo)
: matrixOne{matrixOne}, matrixTwo{matrixTwo} {
    if(!validMultiplication()) {
        validity = false;
        std::cout << PRINT_DIMENSIONS_MATCH << std::endl;
    } else {
        multiply();
    }
}

void MultiplicationMatrix::multiply() {
    
    row = matrixOne.getRow();
    column = matrixTwo.getColumn();

    init();

    for (int rowIndex = 0; rowIndex < row.getRow(); rowIndex++) {
        for (int columnIndex = 0; columnIndex < column.getColumn(); columnIndex++) {
            for (int commonIndex = 0; commonIndex < matrixOne.getColumn(); commonIndex++) {
                *(*(array2D + rowIndex) + columnIndex) += matrixOne.getElement(rowIndex, commonIndex) * matrixTwo.getElement(commonIndex, columnIndex);
            }
        }
    }
}

void MultiplicationMatrix::print() const {
    std::cout << PRINT_RESULT_MATRIX;
    commonPrint();
}

bool MultiplicationMatrix::validMultiplication() {
    bool result = true;
    if (matrixOne.getColumn() != matrixTwo.getRow()) {
        return false;
    }
    return result;
}