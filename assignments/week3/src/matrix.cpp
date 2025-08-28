#include <iostream>
#include "matrix.h"
#include "helper_functions.h"

using namespace std;

void Matrix::init() {
    row = convertToInteger(charRow);
    column = convertToInteger(charColumn);
    matrix = new double*[row];
    for (int index = 0; index < row; index++) {
        matrix[index] = new double[column];
    }
}
void Matrix::init(int row, int column) {
    this->row = row;
    this->column = column;
    matrix = new double*[row];
    for (int index = 0; index < row; index++) {
        matrix[index] = new double[column];
    }
}

void Matrix::print() const {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Matrix::add(const Matrix& firstMatrix, const Matrix& secondMatrix) {
    
    if (firstMatrix.row != secondMatrix.row || firstMatrix.column != secondMatrix.column) {
        cout << "Matrices do not have the same dimensions ! ! ! Try again ! ! !";
        matrix = nullptr;
        return;
    }
    init(firstMatrix.row, firstMatrix.column);

    for (int indexI = 0; indexI < row; indexI++) {
        for (int indexJ = 0; indexJ < column; indexJ++) {
            matrix[indexI][indexJ] = firstMatrix.matrix[indexI][indexJ] + secondMatrix.matrix[indexI][indexJ];
        }
    }
    return;
}

void Matrix::multiply(const Matrix& firstMatrix, const Matrix& secondMatrix) {
    if (firstMatrix.column != secondMatrix.row) {
        cout << "Column of Matrix 1 and Row of Matrix 2 do not match ! ! ! Try again ! ! !" << endl;
        matrix = nullptr;
        return;
    }
    init(firstMatrix.row, secondMatrix.column);
    for (int indexI = 0; indexI < firstMatrix.row; indexI++) {
        for (int indexJ = 0; indexJ < secondMatrix.column; indexJ++) {
            for (int indexK = 0; indexK < firstMatrix.column; indexK++) {
                matrix[indexI][indexJ] += firstMatrix.matrix[indexI][indexK] * secondMatrix.matrix[indexK][indexJ];
            }
        }
    }
    return;
}

Matrix::~Matrix() {

    if(matrix) {
        for (int i = 0; i < row; i++) {
            delete[] matrix[i];
        }
    }
        
    delete[] matrix;
}
