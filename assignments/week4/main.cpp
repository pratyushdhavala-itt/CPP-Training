#include <iostream>
#include "print.h"
#include "option.h"
#include "matrix.h"
#include "element.h"
#include "addition_matrix.h"
#include "multiplication_matrix.h"
#include "exception_handling.h"

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

        Matrix matrices[] {matrixOne, matrixTwo};
        if (!ExceptionHandling::isCompatible(matrixOne, matrixTwo, option)) continue;
        for (int k = 0; k < 2; k++) {
            for (int i = 0; i < matrices[k].getRow(); i++) {
                for (int j = 0; j < matrices[k].getColumn(); j++) {
                    Element element(Row(i), Column(j), matrices[k].getCurrentMatrixCount());
                    cin >> element;
                    matrices[k].setValue(element);
                }
            }
        }


        matrixOne.print();
        matrixTwo.print();

        switch(option.getOperation()) {
            case Option::ADDITION: {
                AdditionMatrix result(matrixOne, matrixTwo);
                result.print();
                break;
            }
            case Option::MULTIPLICATION: {
                MultiplicationMatrix result(matrixOne, matrixTwo);
                result.print();
                break;
            }
        }
    }
    return 0;
}