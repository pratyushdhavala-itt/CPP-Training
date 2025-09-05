#include "addition_matrix.h"
#include "constants.h"

AdditionMatrix::AdditionMatrix(Matrix& matrixOne, Matrix& matrixTwo)
: matrixOne{matrixOne}, matrixTwo{matrixTwo} {
    if (!validAddition()) {
        validity = false;
        std::cout << PRINT_DIMENSIONS_MATCH << std::endl;
    } else {
        add();
    }
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

void AdditionMatrix::print() const {
    std::cout << PRINT_RESULT_MATRIX;
    commonPrint();
}

bool AdditionMatrix::validAddition() {
    bool result = true;
    if (matrixOne.getColumn() != matrixTwo.getColumn() || matrixOne.getRow() != matrixTwo.getRow()) {
        return false;
    }
    return result;
}