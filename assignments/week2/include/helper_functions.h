#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H



extern "C" {

    extern const char* PRINT_ENTER_FIRST_NUMBER;
    extern const char* PRINT_ENTER_SECOND_NUMBER;
    extern const char* PRINT_WRONG_INPUT;
    extern const char* PRINT_REPEAT_STRING;
    extern const char* PRINT_RESULT;

    void handleInputLimitError();
    void printMenu();
    bool isValidMenuOption(char* input);
    bool printChosenOption(const char* input);
    double performChosenOperation(char* firstNumberChar, char* secondNumberChar, const char* input);
    void removeWhiteSpaces(char* input);
    double findPower(double base, double exponent);
    int calculateInputLength(const char* input);
    int convertToInteger(const char* input);
    bool isValidNumber(const char* input);
    int firstDecimalIndex(const char* input);
    bool isValidFloatingPoint(const char* input);
    bool checkForNegative(const char* input);
    int findPreDecimalPointLength(const char* input);
    int findPostDecimalPointLength(const char* input);
    double convertToNumber(const char* input);
    bool repeatProgramOrNot(const char* input);
    double convertToFloatingNumber(const char* input);

}

#endif