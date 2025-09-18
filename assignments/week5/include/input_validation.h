#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

#include <iostream>

class InputValidation {

public:

    static bool isValidUserID(const std::string& userID);
    static bool isValidPassword(const std::string& password);
    static bool isValidAmount(const char* amount);
    static bool isInputTooLong();
    static bool isValidAccountNumber(const char* accountNumber);
    static bool isValidName(const std::string& userName);
    static bool isValidMenuChoice(const char* input);
};

#endif