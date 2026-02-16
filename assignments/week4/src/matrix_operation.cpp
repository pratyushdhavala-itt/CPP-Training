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
    bool result = true;
    if (matrixOne.getColumnCount() != matrixTwo.getRowCount()) {
        return false;
    }
    return result;
}

bool MatrixOperation::validAddition() {
    bool result = true;
    if (matrixOne.getRowCount() != matrixTwo.getRowCount() || matrixOne.getColumnCount() != matrixTwo.getColumnCount()) {
        result = false;
    }
    return result;
}

void MatrixOperation::add() {
    
    for (int rowIndex = 0; rowIndex < matrixOne.matrixRow; rowIndex++) {
        for (int columnIndex = 0; columnIndex < matrixOne.matrixColumn; columnIndex++) {
            *(*(result.matrixArray + rowIndex) + columnIndex) = matrixOne.getElement(rowIndex, columnIndex) + matrixTwo.getElement(rowIndex, columnIndex);
        }
    }
}

