#ifndef MATRIX_H
#define MATRIX_H

#include "input_limit.h"

struct Matrix {
    char charRow[MATRIX_INPUT];
    char charColumn[MATRIX_INPUT];
    int row;
    int column;
    double** matrix;

    void init();
    void init(int row, int column);
    void print() const;

    ~Matrix();
};

#endif