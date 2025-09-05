#include <iostream>
#include "print.h"
#include "option.h"
#include "matrix.h"
#include "element.h"
#include "addition_matrix.h"
#include "multiplication_matrix.h"
#include "exception_handling.h"
#include "matrix_operation.h"

using namespace std;

int main() {
    while (true) {

        Option option;
        cin >> option;
        if (option.getStatus()) break;

        Matrix matrixOne;
        cin >> matrixOne;
        Matrix matrixTwo;
        cin >> matrixTwo;

        if (!ExceptionHandling::isCompatible(matrixOne, matrixTwo, option)) continue;

        Matrix* matrices[] { &matrixOne, &matrixTwo };
        for (int matrixIndex = 0; matrixIndex < 2; matrixIndex++) {
            for (int rowIndex = 0; rowIndex < matrices[matrixIndex]->getRow(); rowIndex++) {
                for (int columnIndex = 0; columnIndex < matrices[matrixIndex]->getColumn(); columnIndex++) {
                    Element element(Row(rowIndex), Column(columnIndex), matrices[matrixIndex]->getCurrentMatrixCount());
                    cin >> element;
                    matrices[matrixIndex]->setValue(element);
                }
            }
        }

        matrixOne.print();
        matrixTwo.print();

        performOperation(option, matrixOne, matrixTwo);
    }
    return 0;
}