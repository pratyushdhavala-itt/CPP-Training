#ifndef MULTIPLICATION_MATRIX_H
#define MULTIPLICATION_MATRIX_H

#include "matrix.h"

class MultiplicationMatrix : public Matrix {

private:
    Matrix& matrixOne;
    Matrix& matrixTwo;

public:

    MultiplicationMatrix(Matrix& matrixOne, Matrix& matrixTwo);
    void multiply();
    bool validMultiplication();
    

};

#endif