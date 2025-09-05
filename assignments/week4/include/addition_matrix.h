#include "matrix.h"

class AdditionMatrix : public Matrix {

private:

    Matrix& matrixOne;
    Matrix& matrixTwo;

public:

    AdditionMatrix(Matrix& matrixOne, Matrix& matrixTwo);
    void add();
    bool validAddition();
    
};