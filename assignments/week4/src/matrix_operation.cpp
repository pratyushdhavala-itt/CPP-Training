#include <iostream>
#include "option.h"
#include "matrix.h"
#include "addition_matrix.h"
#include "matrix_operation.h"
#include "multiplication_matrix.h"
#include "constants.h"


void performOperation(Option& option, Matrix& matrixOne, Matrix& matrixTwo) {
    bool validMatrix = true;
    switch(option.getOperation()) {
        case Option::ADDITION: {
            AdditionMatrix result(matrixOne, matrixTwo);
            if (!result.validity) {
                validMatrix = result.validity;
                break;
            }
            result.print();
            break;
        }
        case Option::MULTIPLICATION: {
            MultiplicationMatrix result(matrixOne, matrixTwo);
            if (!result.validity) {
                validMatrix = result.validity;
                break;
            }
            result.print();
            break;
        }
    }
    if (!validMatrix) {
        return;
    }
    char response;
    std::cout << PRINT_PERFORM_AGAIN << std::endl;
    std::cin >> response;
    if (response != 'y' && response != 'Y') {
        std::cout << PRINT_CHOSE_OTHER_OPTION << std::endl;
        return;
    }
    Option secondOption;
    std::cin >> secondOption;
    performOperation(secondOption, matrixOne, matrixTwo);
}