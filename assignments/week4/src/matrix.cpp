#include <iostream>
#include "matrix.h"
#include "atof_functions.h"
#include "exception_handling.h"
#include "constants.h"

int Matrix::totalMatrixCount = 0;

Matrix::Matrix(char inputMatrixRow[INTEGER_INPUT], char inputMatrixColumn[INTEGER_INPUT]) {
    
    matrixRow = Atof::convertToInteger(inputMatrixRow);
    matrixColumn = Atof::convertToInteger(inputMatrixColumn);

    init();

    totalMatrixCount++;
    currentMatrixCount = totalMatrixCount;
}

Matrix::Matrix(int inputMatrixRow, int inputMatrixColumn) : 
    matrixRow{inputMatrixRow}, matrixColumn{inputMatrixColumn} {

    init();

    totalMatrixCount++;
    currentMatrixCount = totalMatrixCount;
}

void Matrix::init() {
    matrixArray = new double*[matrixRow];
    for (int rowIndex = 0; rowIndex < matrixRow; rowIndex++) {
        *(matrixArray + rowIndex) = new double[matrixColumn];
    }
}

void Matrix::setElement(char element[INTEGER_INPUT], int rowIndex, int& columnIndex) {

    if (!ExceptionHandling::isValidMatrixInput(element)) {
        std::cout << PRINT_MATRIX_INVALID_INPUT << std::endl;
        columnIndex--;
    }
    double matrixElement = Atof::convertToNumber(element);
    *(*(matrixArray + rowIndex) + columnIndex) = matrixElement;
}

int Matrix::getRow() const {
    return matrixRow;
}

int Matrix::getColumn() const {
    return matrixColumn;
}

int Matrix::getCurrentMatrixCount() {
    return currentMatrixCount;
}

double Matrix::getElement(int rowIndex, int columnIndex) {
    return *(*(matrixArray + rowIndex) + columnIndex);
}

void Matrix::print() const {
    std::cout << PRINT_THIS_MATRIX << currentMatrixCount << PRINT_SEMICOLUMN << std::endl;
    displayMatrix();
}

void Matrix::displayMatrix() const {
    for (int rowIndex = 0; rowIndex < getRow(); rowIndex++) {
        for (int columnIndex = 0; columnIndex < getColumn(); columnIndex++) {
            std::cout << *(*(matrixArray + rowIndex) + columnIndex) << " ";
        }
        std::cout << '\n';
    }
}

Matrix::~Matrix() {
    for (int rowIndex = 0; rowIndex < getRow(); rowIndex++) {
        delete[] *(matrixArray + rowIndex);
    }

    delete[] matrixArray;
}


