#include <iostream>
#include <dlfcn.h>
#include "math_operations.h"
#include "helper_functions.h"
struct dynamicFunctions {
    void* handle;

    void (*printMenu)();
    bool (*isValidMenuOption)(char*);
    bool (*printChosenOption)(const char*);
    double (*performChosenOperation)(char*, char*, const char*);
    void (*removeWhiteSpaces)(char*);
    bool (*isValidNumber)(const char*);
    bool (*repeatProgramOrNot)(const char*);

    const char** PRINT_ENTER_FIRST_NUMBER;
    const char** PRINT_ENTER_SECOND_NUMBER;
    const char** PRINT_RESULT;
    const char** PRINT_WRONG_INPUT;
    const char** PRINT_REPEAT_STRING;

    dynamicFunctions() {
        handle = dlopen("./lib/libmylibrary.so", RTLD_LAZY);
        if (!handle) {
            std::cerr << "Error: " << dlerror() << std::endl;
            exit(1);
        }

        printMenu = (decltype(printMenu)) dlsym(handle, "printMenu");
        isValidMenuOption = (decltype(isValidMenuOption)) dlsym(handle, "isValidMenuOption");
        printChosenOption = (decltype(printChosenOption)) dlsym(handle, "printChosenOption");
        performChosenOperation = (decltype(performChosenOperation)) dlsym(handle, "performChosenOperation");
        removeWhiteSpaces = (decltype(removeWhiteSpaces)) dlsym(handle, "removeWhiteSpaces");
        isValidNumber = (decltype(isValidNumber)) dlsym(handle, "isValidNumber");
        repeatProgramOrNot = (decltype(repeatProgramOrNot)) dlsym(handle, "repeatProgramOrNot");
        
        PRINT_ENTER_FIRST_NUMBER = (decltype(PRINT_ENTER_FIRST_NUMBER)) dlsym(handle, "PRINT_ENTER_FIRST_NUMBER");
        PRINT_ENTER_SECOND_NUMBER = (decltype(PRINT_ENTER_SECOND_NUMBER)) dlsym(handle, "PRINT_ENTER_SECOND_NUMBER");
        PRINT_RESULT = (decltype(PRINT_RESULT)) dlsym(handle, "PRINT_RESULT");
        PRINT_WRONG_INPUT = (decltype(PRINT_WRONG_INPUT)) dlsym(handle, "PRINT_WRONG_INPUT");
        PRINT_REPEAT_STRING = (decltype(PRINT_REPEAT_STRING)) dlsym(handle, "PRINT_REPEAT_STRING");

    }

    ~dynamicFunctions() {
        if (handle) dlclose(handle);
    }
};

int main() {
    dynamicFunctions dyFunc;
    char input[100];
    while (true) {
        dyFunc.printMenu();
        std::cin.getline(input, 100);
        if (!dyFunc.isValidMenuOption(input)) {
            continue;
        }
        if (dyFunc.printChosenOption(input)) {

            return 0;
        }
        char charFirstNumber[10];
        char charSecondNumber[10];
        std::cout << *dyFunc.PRINT_ENTER_FIRST_NUMBER;
        std::cin.getline(charFirstNumber, 10);
        std::cout << '\n';
        std::cout << *dyFunc.PRINT_ENTER_SECOND_NUMBER;
        std::cin.getline(charSecondNumber, 10);
        std::cout << '\n';
        dyFunc.removeWhiteSpaces(charFirstNumber);
        dyFunc.removeWhiteSpaces(charSecondNumber);
        if (!dyFunc.isValidNumber(charFirstNumber) || !dyFunc.isValidNumber(charSecondNumber)) {
            std::cout << *dyFunc.PRINT_WRONG_INPUT << std::endl;
            continue;
        }
        double result = dyFunc.performChosenOperation(charFirstNumber, charSecondNumber, input);
        std::cout << *dyFunc.PRINT_RESULT << result << std::endl;
        std::cout << *dyFunc.PRINT_REPEAT_STRING << std::endl;
        char repeatProgram[100];
        std::cin.getline(repeatProgram, 100);
        if (dyFunc.repeatProgramOrNot(repeatProgram)) {
            continue;
        } 
        return 0;
    }
}
