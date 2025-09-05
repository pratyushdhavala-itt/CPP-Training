#ifndef MATRIX_H
#define MATRIX_H

#include "user_option.h"
#include "constants.h"

class Matrix {

protected:

    int matrixRow;
    int matrixColumn;
    double** matrixArray;
    static int totalMatrixCount;
    int currentMatrixCount;

public:

    Matrix(char inputMatrixRow[INTEGER_INPUT], char inputMatrixColumn[INTEGER_INPUT]);
    Matrix(int inputMatrixRow, int inputMatrixColumn);
    void init();
    int getRow() const;
    int getColumn() const;
    int getCurrentMatrixCount();
    void print() const;
    void displayMatrix() const;
    double getElement(int row, int column);
    void setElement(char element[10], int rowIndex, int& columnIndex);

    ~Matrix();

};

#endif
