#ifndef MATRIX_H
#define MATRIX_H

struct Matrix {
    char charRow[10];
    char charColumn[10];
    int row;
    int column;

    double** matrix;

    void init();
    void init(int row, int column);
    void print() const;
    void add(const Matrix& firstMatrix, const Matrix& secondMatrix);
    void multiply(const Matrix& firstMatrix, const Matrix& secondMatrix);
    ~Matrix();
};

#endif