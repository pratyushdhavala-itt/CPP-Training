#include <iostream>
#include "exception_handling.h"
#include "atof_functions.h"
#include "print_functions.h"
#include "matrix.h"
#include "constants.h"

extern bool exitProgram;

int main() {
    while (true) {
        printMenu();
        char input[1];
        std::cin.getline(input, MENU_INPUT);
        handleInputError(MENU_INPUT - 1);
        printOption(input);
        if (exitProgram) break;
        Matrix matrices[2];
        for (int matrixIndex = 0; matrixIndex < 2; matrixIndex++) {
            std::cout << PRINT_ENTER_ROW << matrixIndex + 1 << PRINT_SEMICOLUMN;
            std::cin.getline((*(matrices + matrixIndex)).charRow, MATRIX_INPUT);
            if (!isValidInput((*(matrices + matrixIndex)).charRow, matrixIndex)) continue;
            std::cout << PRINT_ENTER_COLUMN << matrixIndex + 1 << PRINT_SEMICOLUMN;
            std::cin.getline((*(matrices + matrixIndex)).charColumn, MATRIX_INPUT);
            if (!isValidInput((*(matrices + matrixIndex)).charColumn, matrixIndex)) continue;
            matrices[matrixIndex].init();
        }
        if (!isValidMatrix(matrices, input)) continue;
        for (int matrixIndex = 0; matrixIndex < 2; matrixIndex++) {
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
        printInputMatrices(matrices[0], matrices[1]);
        Matrix resultMatrix;
        performMatrixOperation(input, resultMatrix, matrices[0], matrices[1]);
        printResultMatrix(resultMatrix);
    }
    return 0;
}