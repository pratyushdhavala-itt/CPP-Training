#include <iostream>
#include "user_option.h"
#include "matrix.h"
#include "matrix_addition.h"
#include "matrix_multiplication.h"
#include "exception_handling.h"
#include "matrix_operation.h"
#include "constants.h"

using namespace std;

int main() {
    while (true) {

        UserOption userOption;
        cin >> userOption;
        if (userOption.getExitStatus()) break;
        char inputMatrixRow[INTEGER_INPUT];
        char inputMatrixColumn[INTEGER_INPUT];

        while (true) {
            cout << PRINT_ENTER_ROW_MATRIX_ONE;
            cin.getline(inputMatrixRow, INTEGER_INPUT);
            if(!ExceptionHandling::isValidInput(inputMatrixRow)) continue;
            cout << PRINT_ENTER_COLUMN_MATRIX_ONE;
            cin.getline(inputMatrixColumn, INTEGER_INPUT);
            if(!ExceptionHandling::isValidInput(inputMatrixRow)) continue;
            break;
        }
        
        Matrix matrixOne(inputMatrixRow, inputMatrixColumn);

        while (true) {
            cout << PRINT_ENTER_ROW_MATRIX_TWO;
            cin.getline(inputMatrixRow, INTEGER_INPUT);
            if(!ExceptionHandling::isValidInput(inputMatrixRow)) continue;
            cout << PRINT_ENTER_COLUMN_MATRIX_TWO;
            cin.getline(inputMatrixColumn, INTEGER_INPUT);
            if(!ExceptionHandling::isValidInput(inputMatrixRow)) continue;
            break;
        }

        Matrix matrixTwo(inputMatrixRow, inputMatrixColumn);

        if (!ExceptionHandling::canPerformOperation(matrixOne, matrixTwo, userOption)) continue;

        char element[10];

        for (int rowIndex = 0; rowIndex < matrixOne.getRow(); rowIndex++) {
            for (int columnIndex = 0; columnIndex < matrixOne.getColumn(); columnIndex++) {
                cout << PRINT_ENTER_ELEMENT_ONE_1 << rowIndex << PRINT_ENTER_ELEMENT_THREE << columnIndex << PRINT_ENTER_ELEMENT_FOUR;
                cin.getline(element, 10);
                matrixOne.setElement(element, rowIndex, columnIndex);
            }
        }

        for (int rowIndex = 0; rowIndex < matrixTwo.getRow(); rowIndex++) {
            for (int columnIndex = 0; columnIndex < matrixTwo.getColumn(); columnIndex++) {
                cout << PRINT_ENTER_ELEMENT_ONE_2 << rowIndex << PRINT_ENTER_ELEMENT_THREE << columnIndex << PRINT_ENTER_ELEMENT_FOUR;
                cin.getline(element, 10);
                matrixTwo.setElement(element, rowIndex, columnIndex);
            }
        }

        matrixOne.print();
        matrixTwo.print();

        performOperation(userOption, matrixOne, matrixTwo);
        
        while (true) {
            char input;
            cin >> input;
            if (input != 'y' && input != 'Y') {
                cout << PRINT_RESTART_PROGRAM << endl;
                cin.ignore(1000, '\n');
                break;
            } 
            performAnotherOperation(input, matrixOne, matrixTwo);
        }
        
    }
    return 0;
}
