#include <iostream>
#include "row.h"

Row::Row(int row) : matrixRow{row} {}

int Row::getRow() const {
    return matrixRow;
}

// void Row::setRow(int matrixRow) {
//     this->matrixRow = matrixRow;
// }

std::istream& operator >> (std::istream& in, Row& row) {
    in >> row.matrixRow;
    return in;
}