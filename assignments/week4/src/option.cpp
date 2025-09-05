#include <iostream>
#include "exception_handling.h"
#include "constants.h"
#include "option.h"
#include "print.h"

Option::Option() : exitProgram{false} {
    Print::printMenu();
}

std::istream& operator >>(std::istream& in, Option& option) {
    in >> option.input;

    if (ExceptionHandling::inputFail()) {
        option.exitProgram = true;
    } else {
        option.print();
    }

    in.ignore(1000, '\n');
    return in;
}

bool Option::getStatus() {
    return exitProgram;
}

void Option::print() {

    switch(input) {
        case '1':
            std::cout << PRINT_PERFORM_ADDITON << std::endl;
            op = ADDITION;
            break;

        case '2':
            std::cout << PRINT_PERFORM_MULTIPLICATION << std::endl;
            op = MULTIPLICATION;
            break;

        default:
            std::cout << PRINT_EXIT_PROGRAM << std::endl;
            exitProgram = true;
            break;
    }
}

Option::Operation Option::getOperation() {
    return op;
}