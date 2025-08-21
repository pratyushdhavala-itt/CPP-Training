#include <iostream>
#include "./include/math_operations.h"
#include "./include/helper_functions.h"
#include <dlfcn.h>

int main() {

    void* handle = dlopen("./lib/libmylibrary.so", RTLD_LAZY);
    
    double (*addTwoNumbers)(double, double) = (double(*)(double, double)) dlsym(handle, "addTwoNumbers");
    double (*subtractTwoNumbers)(double, double) = (double(*)(double, double)) dlsym(handle, "subtractTwoNumbers");
    double (*multiplyTwoNumbers)(double, double) = (double(*)(double, double)) dlsym(handle, "multiplyTwoNumbers");
    double (*divideTwoNumbers)(double, double) = (double(*)(double, double)) dlsym(handle, "divideTwoNumbers");

    void (*removeWhiteSpaces)(char*) = (void(*)(char*)) dlsym(handle, "removeWhiteSpaces");
    int (*findPower)(double, double) = (int(*)(double, double)) dlsym(handle, "findPower");
    int (*calculateInputLength)(const char*) = (int(*)(const char*)) dlsym(handle, "calculateInputLength");
    int (*convertToInteger)(const char*) = (int(*)(const char*)) dlsym(handle, "convertToInteger");
    bool (*isNotANumber)(const char*) = (bool(*)(const char*)) dlsym(handle, "isNotANumber");
    int (*firstDecimalIndex)(const char*) = (int(*)(const char*)) dlsym(handle, "firstDecimalIndex");
    bool (*isValidFloatingPoint)(const char*) = (bool(*)(const char*)) dlsym(handle, "isValidFloatingPoint");
    bool (*checkForNegative)(const char*) = (bool(*)(const char*)) dlsym(handle, "checkForNegative");
    int (*findPreDecimalPointLength)(const char*) = (int(*)(const char*)) dlsym(handle, "findPreDecimalPointLength");
    int (*findPostDecimalPointLength)(const char*) = (int(*)(const char*)) dlsym(handle, "findPostDecimalPointLength");
    double (*convertToNumber)(const char*) = (double(*)(const char*)) dlsym(handle, "convertToNumber");
    bool (*repeatProgramOrNot)(const char*) = (bool(*)(const char*)) dlsym(handle, "repeatProgramOrNot");
    double (*convertToFloatingNumber)(const char*) = (double(*)(const char*)) dlsym(handle, "convertToFloatingNumber");

    char input[100];

    while (true) {

startAgainLabel:
        std::cout << "Please enter the option from the below list:" << '\n' <<
                     "1. Addition" << '\n' <<
                     "2. Subtraction" << '\n' <<
                     "3. Multiplication" << '\n' <<
                     "4. Division" << '\n' <<
                     "5. Exit Program" <<
        std::endl;
        std::cin.getline(input, 100);
        removeWhiteSpaces(input);
        bool validOption = true;
        if (isNotANumber(input) && isValidFloatingPoint(input)) {
            std::cout << "Not a valid input ! ! !" << std::endl;
            goto startAgainLabel;
        }

        int choice = convertToInteger(input);
        int exitProgram = false;
        switch(choice) {
            case 1:
                std::cout << "Performing addition of two numbers: " << std::endl;
                break;
            
            case 2:
                std::cout << "Performing subtraction of two numbers: " << std::endl;
                break;

            case 3:
                std::cout << "Performing multiplication of two numbers: " << std::endl;
                break;
            
            case 4:
                std::cout << "Performing division of two numbers: " << std::endl;
                break;
            
            case 5:
                std::cout << "Exiting the program ! ! !" << std::endl;
                exitProgram = true;
                break;

            default: 
                std::cout << "Please input an option from 1 to 5" << std::endl;
                goto startAgainLabel;
        }

        if (exitProgram) {
            return 0;
        }
        
        char charFirstNumber[10];
        char charSecondNumber[10];
        std::cout << "Please enter the first number: ";
        std::cin.getline(charFirstNumber, 10);
        std::cout << '\n';
        std::cout << "Please enter the second number: ";
        std::cin.getline(charSecondNumber, 10);
        std::cout << '\n';
        if (isNotANumber(charFirstNumber) || isNotANumber(charSecondNumber)) {
            std::cout << "Wrong input ! ! !" << std::endl;
            goto startAgainLabel;
        }

        double firstNumber = convertToNumber(charFirstNumber);
        double secondNumber = convertToNumber(charSecondNumber);
        std::cout << "First: " << firstNumber << std::endl;
        double result = 0.0;
        switch(choice) {
            case 1:
                result = addTwoNumbers(firstNumber, secondNumber);
                break;
            
            case 2:
                result = subtractTwoNumbers(firstNumber, secondNumber);
                break;

            case 3:
                result = multiplyTwoNumbers(firstNumber, secondNumber);
                break;

            case 4:
                result = divideTwoNumbers(firstNumber, secondNumber);
                break;
        }

        std::cout << "Result: " << result << std::endl;
        std::cout << "Do you want to continue? (y/Y). Enter any other key to exit." << std::endl;
        char repeatProgram[100];
        std::cin.getline(repeatProgram, 100);
        if (repeatProgramOrNot(repeatProgram)) {
            goto startAgainLabel;
        } else {
            return 0;
        }
    }
}
