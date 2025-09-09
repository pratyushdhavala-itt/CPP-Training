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
    int getRowCount() const;
    int getColumnCount() const;
    int getCurrentMatrixCount();
    void print() const;
    void displayMatrix() const;
    double getElement(int row, int column);
    void setElement(char element[INTEGER_INPUT], int rowIndex, int& columnIndex);
    friend class MatrixOperation;


    ~Matrix();

};

#endif
