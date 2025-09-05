#include <iostream>
#include "row.h"

Row::Row(int row) : matrixRow{row} {}

int Row::getRow() const {
    return matrixRow;
}

std::istream& operator >> (std::istream& in, Row& row) {
    in >> row.matrixRow;
    return in;
}