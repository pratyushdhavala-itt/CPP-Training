#include <iostream>
#include "matrix.h"
#include "element.h"
#include "atof.h"
#include "exception_handling.h"

int Matrix::totalMatrixCount = 0;

Matrix::Matrix() {
    totalMatrixCount++;
    currentMatrixCount = totalMatrixCount;
}

std::istream& operator >> (std::istream& in, Matrix& matrix) {
    char row[10];
    char column[10];
    while (true) {
        std::cout << "Enter row for Matrix " << matrix.currentMatrixCount << ": ";
        in.getline(row, 10);
        if (ExceptionHandling::isValidInput(row)) {
            break;
        }
    }
    
    while (true) {
        std::cout << "Enter column for Matrix " << matrix.currentMatrixCount << ": ";
        in.getline(column, 10);
        if (ExceptionHandling::isValidInput(column)) {
            break;
        }
    }

    
    matrix.row = Atof::convertToNumber(row);
    matrix.column = Atof::convertToNumber(column);
    
    //in.ignore(100000, '\n');
    matrix.init();
    return in;
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

void Matrix::init() {
    array2D = new int*[row.getRow()];
    for (int i = 0; i < row.getRow(); i++) {
        array2D[i] = new int[column.getColumn()];
    }
}

void Matrix::setValue(Element& element) {
    *(*(array2D + element.getRow()) + element.getColumn()) = element.getValue();
}

void Matrix::print() const {
    for (int i = 0; i < row.getRow(); i++) {
        for (int j = 0; j < column.getColumn(); j++) {
            std::cout << *(*(array2D + i) + j) << " ";
        }
        std::cout << '\n';
    }
}

double Matrix::getElement(int row, int column) {
    return *(*(array2D + row) + column);
}