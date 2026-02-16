#ifndef MATRIX_OPERATION_H
#define MATRIX_OPERATION_H

#include "user_option.h"
#include "matrix.h"
#include "constants.h"

class MatrixOperation {

private:

    Matrix& matrixOne;
    Matrix& matrixTwo;
    Matrix result;

public:
    MatrixOperation(Matrix& matrixOne, Matrix& matrixTwo);
    void add();
    void multiply();
    bool validMultiplication();
    bool validAddition();
    void print() const;

    friend void performOperation(MatrixOperation& matrixOperation, UserOption& userOption);

};


#endif
