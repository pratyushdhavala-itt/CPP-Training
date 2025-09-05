#include <iostream>
#include "user_option.h"
#include "matrix.h"
#include "matrix_addition.h"
#include "matrix_operation.h"
#include "matrix_multiplication.h"
#include "constants.h"


void performOperation(UserOption& userOption, Matrix& matrixOne, Matrix& matrixTwo) {

    bool validMatrix = true;
    
    switch(userOption.getOperation()) {
        case UserOption::ADDITION: {
            AdditionMatrix result(matrixOne, matrixTwo);
            if (!result.validity) {
                validMatrix = result.validity;
                break;
            }
            result.print();
            break;
        }
        case UserOption::MULTIPLICATION: {
            MultiplicationMatrix result(matrixOne, matrixTwo);
            if (!result.validity) {
                validMatrix = result.validity;
                break;
            }
            result.print();
            break;
        }
    }
    std::cout << PRINT_PERFORM_AGAIN << std::endl;
}

void performAnotherOperation(char input, Matrix& matrixOne, Matrix& matrixTwo) {

    std::cin.ignore(IGNORE_INPUT, '\n');
    UserOption userOption;
    std::cin >> userOption;

    performOperation(userOption, matrixOne, matrixTwo);

}
