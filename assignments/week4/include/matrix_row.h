#ifndef ROW_H
#define ROW_H

#include <iostream>

class Row {

private:

    int matrixRow;

public:

    int getRow() const;
    // void setRow(int row);

    Row() = default;
    Row(int row);

    friend std::istream& operator >> (std::istream& in, Row& row);
};

#endif