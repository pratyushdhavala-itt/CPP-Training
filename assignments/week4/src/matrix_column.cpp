#include <iostream>
#include "column.h"

Column::Column(int column) : matrixColumn{column} {}

int Column::getColumn() const {
    return matrixColumn;
}

std::istream& operator >> (std::istream& in, Column& column) {
    in >> column.matrixColumn;
    return in;
}