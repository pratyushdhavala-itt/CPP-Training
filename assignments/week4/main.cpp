#include <iostream>
#include "user_option.h"
#include "matrix.h"
#include "exception_handling.h"
#include "matrix_operation.h"
#include "constants.h"

void matrixDimensionInput(char inputMatrixRow[], char inputMatrixColumn[], MatrixIndex matrixIndex);
void matrixElementInput(Matrix& matrix);

int main() {
    while (true) {

        UserOption userOption;
        std::cin >> userOption;
        if (userOption.getExitStatus()) break;
        char inputMatrixRow[INTEGER_INPUT];
        char inputMatrixColumn[INTEGER_INPUT];

        matrixDimensionInput(inputMatrixRow, inputMatrixColumn, FIRST_MATRIX);
        Matrix matrixOne(inputMatrixRow, inputMatrixColumn);

        matrixDimensionInput(inputMatrixRow, inputMatrixColumn, SECOND_MATRIX);
        Matrix matrixTwo(inputMatrixRow, inputMatrixColumn);

        if (!ExceptionHandling::canPerformOperation(matrixOne, matrixTwo, userOption)) continue;

        matrixElementInput(matrixOne);
        matrixElementInput(matrixTwo);

        matrixOne.print();
        matrixTwo.print();

        MatrixOperation operation(matrixOne, matrixTwo);
        operation.performOperation(userOption);
        
        while (true) {
            char input;
            std::cin >> input;
            if (input != 'y' && input != 'Y') {
                std::cout << PRINT_RESTART_PROGRAM << std::endl;
                std::cin.ignore(IGNORE_INPUT, '\n');
                break;
            } 
            operation.performAnotherOperation();
        }
        
    }
    return 0;
}

void matrixElementInput(Matrix& matrix) {
    char element[INTEGER_INPUT];
    for (int rowIndex = 0; rowIndex < matrix.getRowCount(); rowIndex++) {
        for (int columnIndex = 0; columnIndex < matrix.getColumnCount(); columnIndex++) {
            std::cout << PRINT_ENTER_ELEMENT_ONE_1 << rowIndex << PRINT_ENTER_ELEMENT_THREE << columnIndex << PRINT_ENTER_ELEMENT_FOUR;
            std::cin.getline(element, INTEGER_INPUT);
            matrix.setElement(element, rowIndex, columnIndex);
        }
    }
}

void matrixDimensionInput(char inputMatrixRow[], char inputMatrixColumn[], MatrixIndex matrixIndex) {

    while (true) {
        if (matrixIndex == FIRST_MATRIX) std::cout << PRINT_ENTER_ROW_MATRIX_ONE;
        if (matrixIndex == SECOND_MATRIX) std::cout << PRINT_ENTER_ROW_MATRIX_TWO;
        std::cin.getline(inputMatrixRow, INTEGER_INPUT);
        if(!ExceptionHandling::isValidInput(inputMatrixRow)) continue;
        if (matrixIndex == FIRST_MATRIX) std::cout << PRINT_ENTER_COLUMN_MATRIX_ONE;
        if (matrixIndex == SECOND_MATRIX) std::cout << PRINT_ENTER_COLUMN_MATRIX_TWO;
        std::cin.getline(inputMatrixColumn, INTEGER_INPUT);
        if(!ExceptionHandling::isValidInput(inputMatrixRow)) continue;
        break;
    }
}