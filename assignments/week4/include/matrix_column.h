#ifndef COLUMN_H
#define COLUMN_H

#include <iostream>

class Column {

private:

    int matrixColumn;

public:
    
    Column() = default;
    
    Column(int column);

    int getColumn() const;

    // void setColumn(int column);

    friend std::istream& operator >> (std::istream& in, Column& column);
};

#endif