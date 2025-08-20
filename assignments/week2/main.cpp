#include <iostream>
#include "./include/math_operations.h"
#include "./include/helper_functions.h"


int main() {

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
            // validOption = false;
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
                // validOption = false;
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
                result = multipyTwoNumbers(firstNumber, secondNumber);
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
