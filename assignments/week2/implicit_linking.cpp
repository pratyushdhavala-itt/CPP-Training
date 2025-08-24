#include <iostream>
#include <dlfcn.h>
#include "math_operations.h"
#include "helper_functions.h"

int main() {
    char input[100];
    while (true) {
        printMenu();
        std::cin.getline(input, 100);
        if (!isValidMenuOption(input)) {
            continue;
        }
        if (printChosenOption(input)) {

            return 0;
        }
        char charFirstNumber[10];
        char charSecondNumber[10];
        std::cout << PRINT_ENTER_FIRST_NUMBER;
        std::cin.getline(charFirstNumber, 10);
        std::cout << '\n';
        std::cout << PRINT_ENTER_SECOND_NUMBER;
        std::cin.getline(charSecondNumber, 10);
        std::cout << '\n';
        removeWhiteSpaces(charFirstNumber);
        removeWhiteSpaces(charSecondNumber);
        if (!isValidNumber(charFirstNumber) || !isValidNumber(charSecondNumber)) {
            std::cout << PRINT_WRONG_INPUT << std::endl;
            continue;
        }
        double result = performChosenOperation(charFirstNumber, charSecondNumber, input);
        std::cout << PRINT_RESULT << result << std::endl;
        std::cout << PRINT_REPEAT_STRING << std::endl;
        char repeatProgram[100];
        std::cin.getline(repeatProgram, 100);
        if (repeatProgramOrNot(repeatProgram)) {
            continue;
        } 
        return 0;
    }
}
