#ifndef ADDITION_MATRIX_H
#define ADDITION_MATRIX_H

#include "matrix.h"

class AdditionMatrix : public Matrix {

private:

    Matrix& matrixOne;
    Matrix& matrixTwo;
    bool validity;

public:

    AdditionMatrix(Matrix& matrixOne, Matrix& matrixTwo);
    void add();
    bool validAddition();
    void print() const;
    
    friend void performOperation(Option& option, Matrix& matrixOne, Matrix& matrixTwo);
};

#endif