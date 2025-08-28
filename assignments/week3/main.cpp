#include <iostream>
#include "helper_functions.h"
#include "matrix.h"
#include "constants.h"
using namespace std;

extern bool exitProgram;

int main() {
    while (true) {
        printMenu();
        char input[1];
        cin.getline(input, 2);
        inputFail(1);
        printChosenOption(input);
        if (exitProgram) {
            exitProgram = false;
            break;
        }
        Matrix matrices[2];
        for (int matrixIndex = 0; matrixIndex < 2; matrixIndex++) {
            cout << PRINT_ENTER_ROW << matrixIndex + 1 << ": ";
            cin.getline(matrices[matrixIndex].charRow, 10);
            if (!isValidRowOrColumn(matrices[matrixIndex].charRow)) {
                matrixIndex--; 
                continue;
            }
            cout << PRINT_ENTER_COLUMN << matrixIndex + 1 << ": ";
            cin.getline(matrices[matrixIndex].charColumn, 10);
            if (!isValidRowOrColumn(matrices[matrixIndex].charColumn)){
                matrixIndex--;
                continue;
            }
            matrices[matrixIndex].init();
        }
        if (!isValidMatrix(matrices, input)) continue;
        for (int matrixIndex = 0; matrixIndex < 2; matrixIndex++) {
            for (int indexI = 0; indexI < matrices[matrixIndex].row; indexI++) {
                for (int indexJ = 0; indexJ < matrices[matrixIndex].column; indexJ++) {
                    char charElement[10];
                    cout << "Enter element for matrix " << matrixIndex + 1 << " for position [" << indexI << "][" << indexJ << "]: ";
                    cin.getline(charElement, 10);
                    if (inputFail(10) || !isValidNumber(charElement)) {
                        cout << PRINT_INVALID_INPUT << endl;
                        indexJ--;
                        continue;
                    }
                    double element = convertToNumber(charElement);
                    matrices[matrixIndex].matrix[indexI][indexJ] = element;
                }
            }
        }
        Matrix resultMatrix;
        performMatrixOperation(input, resultMatrix, matrices[0], matrices[1]);
        resultMatrix.print();
    }
    return 0;
}