#include <iostream>
#include <cstring>
#include "input_validation.h"

bool InputValidation::isValidUserID(const std::string& userID) {
    bool result = true;
    if (userID.empty()) {
        result = false;
    }
    if (userID.size() < 3 || userID.size() > 20) {
        result = false;
    }
    for (char c : userID) {
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')) {
            result = false;
            break;
        }
    }
    return result;
}

bool InputValidation::isValidPassword(const std::string& password) {
    bool result = true;
    if (password.size() < 4 || password.size() > 20) {
        result = false;
    }
    for (char c : password) {
        if (c == ' ') {
            result = false;
            break;
        }
    }
    return result;
}

bool InputValidation::isValidAmount(const char* input) {
    bool result = true;
    bool hasDecimal = false;
    if (isInputTooLong()) {
        result = false;
    }
    if (input == nullptr || *input == '\0') {
        result = false;
    }
    for(int index = 0; input[index] != '\0'; index++) {
        char c = input[index];
        if ((c >= '0' && c <= '9')) {
            continue;
        } else if (c == '.' && !hasDecimal) {
            hasDecimal = true;
        } else {
            result = false;
            break;
        }
    }
    return result;
}

bool InputValidation::isInputTooLong() {
    bool result = false;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        result = true;
    }
    return result;
}

bool InputValidation::isValidAccountNumber(const char* accountNumber) {
    bool result = true;

    if (isInputTooLong()) {
        result = false;
    }

    if (accountNumber == nullptr || *accountNumber == '\0') {
        result = false;
    }
    if (strlen(accountNumber) != 4) {
        result = false;
    }
    for (int index = 0; accountNumber[index] != '\0'; index++) {
        char c = accountNumber[index];
        if (!(c >= '0' && c <= '9')) {
            result = false;
            break;
        }
    }

    return result;
}

bool InputValidation::isValidName(const std::string& userName) {
    bool result = true;
    if (userName.empty()) {
        result = false;
    }

    char firstLetter = userName[0];
    if (!(firstLetter >= 'A' && firstLetter <= 'Z')) {
        result = false;
    }

    for (int index = 1; index < userName.size(); index++) {
        char c = userName[index];
        if (!(c >= 'a' && c <= 'z')) {
            result = false;
            break;
        }
    }
    return result;
}

bool InputValidation::isValidMenuChoice(const char* input) {
    bool result = true;
    if (input == nullptr || *input == '\0') {
        result = false;
    }
    if (strlen(input) != 1) {
        result = false;
    }
    if (isInputTooLong()) {
        result = false;
    }
    if (!(input[0] == '1' || input[0] == '2')) {
        result = false;
    }
    return result;
}