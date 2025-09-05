#ifndef MULTIPLICATION_MATRIX_H
#define MULTIPLICATION_MATRIX_H

#include "matrix.h"
#include "constants.h"

class MultiplicationMatrix : public Matrix {

private:

    Matrix& matrixOne;
    Matrix& matrixTwo;
    bool validity;

public:

    MultiplicationMatrix(Matrix& matrixOne, Matrix& matrixTwo);
    void multiply();
    bool validMultiplication();
    void print() const;
    
    friend void performOperation(UserOption& userOption, Matrix& matrixOne, Matrix& matrixTwo);

};

#endif
