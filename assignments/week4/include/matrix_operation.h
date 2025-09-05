#ifndef MATRIX_OPERATION_H
#define MATRIX_OPERATION_H

#include "user_option.h"
#include "matrix.h"
#include "constants.h"

void performOperation(UserOption& userOption, Matrix& matrixOne, Matrix& matrixTwo);
void performAnotherOperation(char input, Matrix& matrixOne, Matrix& matrixTwo);

#endif
