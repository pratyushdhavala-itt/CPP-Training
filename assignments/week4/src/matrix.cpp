#include <iostream>
#include "matrix.h"
#include "element.h"
#include "atof.h"
#include "exception_handling.h"
#include "constants.h"

int Matrix::totalMatrixCount = 0;

Matrix::Matrix() {
    totalMatrixCount++;
    currentMatrixCount = totalMatrixCount;
}

int Matrix::getRow() const {
    return row.getRow();
}

int Matrix::getColumn() const {
    return column.getColumn();
}

int Matrix::getCurrentMatrixCount() {
    return currentMatrixCount;
}

void Matrix::setValue(Element& element) {
    *(*(array2D + element.getRow()) + element.getColumn()) = element.getValue();
}

double Matrix::getElement(int rowIndex, int columnIndex) {
    return *(*(array2D + rowIndex) + columnIndex);
}

void Matrix::init() {
    array2D = new double*[row.getRow()];
    for (int rowIndex = 0; rowIndex < row.getRow(); rowIndex++) {
        *(array2D + rowIndex) = new double[column.getColumn()];
    }
}

void Matrix::print() const {
    std::cout << PRINT_THIS_MATRIX << currentMatrixCount << PRINT_SEMICOLUMN << std::endl;
    commonPrint();
}

void Matrix::commonPrint() const {
    for (int rowIndex = 0; rowIndex < row.getRow(); rowIndex++) {
        for (int columnIndex = 0; columnIndex < column.getColumn(); columnIndex++) {
            std::cout << *(*(array2D + rowIndex) + columnIndex) << " ";
        }
        std::cout << '\n';
    }
}

std::istream& operator >> (std::istream& in, Matrix& matrix) {
    char row[10];
    char column[10];
    while (true) {
        std::cout << PRINT_ENTER_ROW << matrix.currentMatrixCount << PRINT_SEMICOLUMN;
        in.getline(row, 10);
        if (ExceptionHandling::isValidInput(row)) {
            break;
        }
    }
    
    while (true) {
        std::cout << PRINT_ENTER_COLUMN << matrix.currentMatrixCount << PRINT_SEMICOLUMN;
        in.getline(column, 10);
        if (ExceptionHandling::isValidInput(column)) {
            break;
        }
    }

    matrix.row = Atof::convertToNumber(row);
    matrix.column = Atof::convertToNumber(column);
    
    matrix.init();
    return in;
}

Matrix::~Matrix() {
    totalMatrixCount--;
    for (int rowIndex = 0; rowIndex < row.getRow(); rowIndex++) {
        delete[] *(array2D + rowIndex);
    }

    delete[] array2D;
}

