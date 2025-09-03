#include <iostream>
#include "exception_handling.h"
#include "atof_functions.h"
#include "print_functions.h"
#include "matrix.h"
#include "constants.h"
#include "input_limit.h"

extern bool exitProgram;

int main() {
    while (true) {

        printMenu();
        char input[MENU_INPUT - 1];
        std::cin.getline(input, MENU_INPUT);
        handleInputError(MENU_INPUT - 1);
        printOption(input);
        if (exitProgram) break;

        Matrix matrices[MATRIX_ARRAY_ELEMENTS];

        for (int matrixIndex = 0; matrixIndex < MATRIX_ARRAY_ELEMENTS; matrixIndex++) {
            std::cout << PRINT_ENTER_ROW << matrixIndex + 1 << PRINT_SEMICOLUMN;
            std::cin.getline((*(matrices + matrixIndex)).charRow, MATRIX_INPUT);
            if (!isValidInput((*(matrices + matrixIndex)).charRow, matrixIndex)) continue;
            std::cout << PRINT_ENTER_COLUMN << matrixIndex + 1 << PRINT_SEMICOLUMN;
            std::cin.getline((*(matrices + matrixIndex)).charColumn, MATRIX_INPUT);
            if (!isValidInput((*(matrices + matrixIndex)).charColumn, matrixIndex)) continue;
            matrices[matrixIndex].init();
        }

        if (!isValidMatrix(matrices, input)) continue;

        for (int matrixIndex = 0; matrixIndex < MATRIX_ARRAY_ELEMENTS; matrixIndex++) {
            for (int rowIndex = 0; rowIndex < (*(matrices + matrixIndex)).row; rowIndex++) {
                for (int columnIndex = 0; columnIndex < (*(matrices + matrixIndex)).column; columnIndex++) {
                    char charElement[MATRIX_INPUT];
                    std::cout << PRINT_ENTER_ELEMENT_ONE << matrixIndex + 1 << PRINT_ENTER_ELEMENT_TWO << rowIndex << PRINT_ENTER_ELEMENT_THREE << columnIndex << PRINT_ENTER_ELEMENT_FOUR;
                    std::cin.getline(charElement, MATRIX_INPUT);
                    if (!isValidMatrixInput(charElement, columnIndex)) continue;
                    double element = convertToNumber(charElement);
                    *(*(((*(matrices + matrixIndex)).matrix) + rowIndex) + columnIndex) = element;
                }
            }
        }

        printInputMatrices(matrices[FIRST_MATRIX_INDEX], matrices[SECOND_MATRIX_INDEX]);
        Matrix resultMatrix;

        performMatrixOperation(input, resultMatrix, matrices[FIRST_MATRIX_INDEX], matrices[SECOND_MATRIX_INDEX]);
        printResultMatrix(resultMatrix);
    }
    return 0;
}