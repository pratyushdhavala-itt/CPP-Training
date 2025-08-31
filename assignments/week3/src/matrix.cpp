#include <iostream>
#include "matrix.h"
#include "atof_functions.h"
#include "print_functions.h"
#include "exception_handling.h"


void Matrix::init() {
    row = convertToInteger(charRow);
    column = convertToInteger(charColumn);
    matrix = new double*[row];
    for (int index = 0; index < row; index++) {
        *(matrix + index) = new double[column];
    }
}
void Matrix::init(int row, int column) {
    this->row = row;
    this->column = column;
    matrix = new double*[row];
    for (int index = 0; index < row; index++) {
        *(matrix + index) = new double[column];
    }
}

void Matrix::print() const {
    for (int rowIndex = 0; rowIndex < row; rowIndex++) {
        for (int columnIndex = 0; columnIndex < column; columnIndex++) {
            std::cout << *(*(matrix + rowIndex) + columnIndex) << " ";
        }
        std::cout << std::endl;
    }
}

void Matrix::add(const Matrix& firstMatrix, const Matrix& secondMatrix) {
    init(firstMatrix.row, firstMatrix.column);
    for (int rowIndex = 0; rowIndex < row; rowIndex++) {
        for (int columnIndex = 0; columnIndex < column; columnIndex++) {
            *(*(matrix + rowIndex) + columnIndex) = *(*(firstMatrix.matrix + rowIndex) + columnIndex) + *(*(secondMatrix.matrix + rowIndex) + columnIndex);
        }
    }
    return;
}

void Matrix::multiply(const Matrix& firstMatrix, const Matrix& secondMatrix) {
    init(firstMatrix.row, secondMatrix.column);
    for (int rowIndex = 0; rowIndex < firstMatrix.row; rowIndex++) {
        for (int columnIndex = 0; columnIndex < secondMatrix.column; columnIndex++) {
            for (int commonIndex = 0; commonIndex < firstMatrix.column; commonIndex++) {
                *(*(matrix + rowIndex) + columnIndex) += *(*(firstMatrix.matrix + rowIndex) + commonIndex) * *(*(secondMatrix.matrix + commonIndex) + columnIndex);
            }
        }
    }
    return;
}

Matrix::~Matrix() {
    if(matrix) {
        for (int rowIndex = 0; rowIndex < row; rowIndex++) {
            delete[] *(matrix + rowIndex);
        }
    }
    delete[] matrix;
}
