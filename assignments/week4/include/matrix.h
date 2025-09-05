#ifndef MATRIX_H
#define MATRIX_H

#include "row.h"
#include "column.h"
#include "element.h"
#include "option.h"

class Matrix {

protected:

    Row row;
    Column column;
    double** array2D;
    static int totalMatrixCount;
    int currentMatrixCount;

public:

    Matrix();

    // bool isValid(Option& option);
    int getRow() const;
    int getColumn() const;
    int getCurrentMatrixCount();
    void setValue(Element& element);
    void init();
    void print() const;
    void commonPrint() const;
    double getElement(int row, int column);

    friend std::istream& operator >> (std::istream& in, Matrix& matrix);

    ~Matrix();

};

#endif