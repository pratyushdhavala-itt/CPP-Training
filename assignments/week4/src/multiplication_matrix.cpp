#include "multiplication_matrix.h"

MultiplicationMatrix::MultiplicationMatrix(Matrix& matrixOne, Matrix& matrixTwo)
: matrixOne{matrixOne}, matrixTwo{matrixTwo} {
    if (validMultiplication()) {
        multiply();
    } else {
        std::cout << "Dimensions do not match" << std::endl;
    }
}

void MultiplicationMatrix::multiply() {
    
    row = matrixOne.getRow();
    column = matrixTwo.getColumn();

    init();

    for (int i = 0; i < row.getRow(); i++) {
        for (int j = 0; j < column.getColumn(); j++) {
            for (int k = 0; k < matrixOne.getColumn(); k++) {
                *(*(array2D + i) + j) += matrixOne.getElement(i, k) * matrixTwo.getElement(k, j);
            }
        }
    }
}

bool MultiplicationMatrix::validMultiplication() {
    bool result = true;
    if (matrixOne.getColumn() != matrixTwo.getRow()) {
        return false;
    }
    return result;
}