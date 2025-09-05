#include "element.h"
#include "constants.h"
#include "atof.h"
#include <iostream>
#include "exception_handling.h"

Element::Element(Row inputRow, Column inputColumn, int matrixCount) 
    : row{inputRow}, column{inputColumn} {
    
    std::cout << PRINT_ENTER_ELEMENT_ONE << matrixCount << PRINT_ENTER_ELEMENT_TWO << row.getRow() 
              << PRINT_ENTER_ELEMENT_THREE << column.getColumn() << PRINT_ENTER_ELEMENT_FOUR;       

}

std::istream& operator >> (std::istream& in, Element& element) {

    while (true) {
        in.getline(element.charValue, 10);
        if (in.fail()) {
            in.clear();
            in.ignore(1000, '\n');
        }
        if (ExceptionHandling::isValidMatrixInput(element.charValue)) {
            break;
        } else {
            std::cout << "Enter value again: ";
        }
    }

    element.value = Atof::convertToNumber(element.charValue);
    
    return in;
}

int Element::getRow() {
    return row.getRow();
}

int Element::getColumn() {
    return column.getColumn();
}

double Element::getValue() {
    return value;
}