#include <iostream>
#include "exception_handling.h"
#include "constants.h"
#include "user_option.h"

UserOption::UserOption() : exitProgram{false} {
    printMenu();
}

bool UserOption::getExitStatus() {
    return exitProgram;
}

UserOption::Operation UserOption::getOperation() {
    return operation;
}

std::istream& operator >>(std::istream& in, UserOption& userOption) {
    userOption.input = in.get();
    userOption.print();
    in.ignore(IGNORE_INPUT, '\n');
    return in;
}

void UserOption::printMenu() {
    std::cout << PRINT_MENU << std::endl;
}

void UserOption::print() {

    switch(input) {
        case '1':
            std::cout << PRINT_PERFORM_ADDITON << std::endl;
            operation = ADDITION;
            break;

        case '2':
            std::cout << PRINT_PERFORM_MULTIPLICATION << std::endl;
            operation = MULTIPLICATION;
            break;

        default:
            std::cout << PRINT_EXIT_PROGRAM << std::endl;
            exitProgram = true;
            break;
    }
}


