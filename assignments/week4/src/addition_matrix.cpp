#include "addition_matrix.h"

AdditionMatrix::AdditionMatrix(Matrix& matrixOne, Matrix& matrixTwo)
: matrixOne{matrixOne}, matrixTwo{matrixTwo} {

    if (validAddition()) {
        add();
    } else {
        std::cout << "Dimensions do not match" << std::endl;
    }
}

bool AdditionMatrix::validAddition() {
    bool result = true;
    if (matrixOne.getRow() != matrixTwo.getRow() || matrixOne.getColumn() != matrixTwo.getColumn()) {
        result = false;
    }
    return result;
}

void AdditionMatrix::add() {

    row = matrixOne.getRow();
    column = matrixOne.getColumn();
    
    init();

    for (int i = 0; i < row.getRow(); i++) {
        for (int j = 0; j < column.getColumn(); j++) {
            *(*(array2D + i) + j) = matrixOne.getElement(i, j) + matrixTwo.getElement(i, j);
        }
    }
}
