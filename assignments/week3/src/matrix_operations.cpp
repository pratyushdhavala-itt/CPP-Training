#include "matrix.h"
#include "matrix_operations.h"

void addTwoMatrices(Matrix& resultMatrix, const Matrix& firstMatrix, const Matrix& secondMatrix) {
    resultMatrix.init(firstMatrix.row, firstMatrix.column);
    for (int rowIndex = 0; rowIndex < resultMatrix.row; rowIndex++) {
        for (int columnIndex = 0; columnIndex < resultMatrix.column; columnIndex++) {
            *(*(resultMatrix.matrix + rowIndex) + columnIndex) = *(*(firstMatrix.matrix + rowIndex) + columnIndex) + *(*(secondMatrix.matrix + rowIndex) + columnIndex);
        }
    }
    return;
}

void multiplyTwoMatrices(Matrix& resultMatrix, const Matrix& firstMatrix, const Matrix& secondMatrix) {
    resultMatrix.init(firstMatrix.row, secondMatrix.column);
    for (int rowIndex = 0; rowIndex < firstMatrix.row; rowIndex++) {
        for (int columnIndex = 0; columnIndex < secondMatrix.column; columnIndex++) {
            for (int commonIndex = 0; commonIndex < firstMatrix.column; commonIndex++) {
                *(*(resultMatrix.matrix + rowIndex) + columnIndex) += *(*(firstMatrix.matrix + rowIndex) + commonIndex) * *(*(secondMatrix.matrix + commonIndex) + columnIndex);
            }
        }
    }
    return;
}