#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include "row.h"
#include "column.h"

class Element {

    Row row;
    Column column;
    char charValue[10];
    double value;

public:
    Element(Row row, Column column, int matrixCount);

    double getValue();
    
    int getRow();

    int getColumn();

    friend std::istream& operator >> (std::istream& in, Element& element);
};

#endif