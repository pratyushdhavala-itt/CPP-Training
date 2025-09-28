#include <iostream>
#include <cstring>

#include "input_validation.h"
#include "constants.h"

bool InputValidation::isValidUserID(const std::string& userID) {
    bool result = true;
    if (userID.empty()) {
        result = false;
    }
    if (userID.size() < USER_ID_MIN_LENGTH || userID.size() > USER_ID_MAX_LENGTH) {
        result = false;
    }
    for (char currentChar : userID) {
        if (!((currentChar >= '0' && currentChar <= '9') || 
            (currentChar >= 'A' && currentChar <= 'Z') || 
            (currentChar >= 'a' && currentChar <= 'z') || 
            (currentChar == '_'))) {
            result = false;
            break;
        }
    }
    return result;
}

bool InputValidation::isValidPassword(const std::string& password) {
    bool result = true;
    if (password.size() < PASSWORD_MIN_LENGTH || password.size() > PASSWORD_MAX_LENGTH) {
        result = false;
    }
    for (char currentChar : password) {
        if (currentChar == ' ') {
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
        std::cin.ignore(IGNORE_CHARACTER_BUFFER, '\n');
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
    if (strlen(accountNumber) != ACCOUNT_NO_LENGTH) {
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

    char firstLetter = userName[ARRAY_FIRST_INDEX];
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
    if (strlen(input) != INPUT_MENU_LENGTH) {
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