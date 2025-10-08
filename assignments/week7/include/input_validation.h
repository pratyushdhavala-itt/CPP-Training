#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

#include <iostream>

class InputValidation {

public:

    virtual bool isValidUserID(const std::string& userID);
    virtual bool isValidPassword(const std::string& password);
    virtual bool isValidAmount(const char* amount);
    virtual bool isInputTooLong();
    virtual bool isValidAccountNumber(const char* accountNumber);
    virtual bool isValidName(const std::string& userName);
    virtual bool isValidMenuChoice(const char* input);
};

#endif