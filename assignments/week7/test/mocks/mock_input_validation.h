#include <gmock/gmock.h>
#include "input_validation.h"

class MockInputValidation : public InputValidation {
public:
    MOCK_METHOD(bool, isValidUserID, (const std::string& userID), (override));
    MOCK_METHOD(bool, isValidPassword, (const std::string& password), (override));
    MOCK_METHOD(bool, isValidAmount, (const char* amount), (override));
    MOCK_METHOD(bool, isInputTooLong, (), (override));
    MOCK_METHOD(bool, isValidAccountNumber, (const char* accountNumber), (override));
    MOCK_METHOD(bool, isValidName, (const std::string& userName), (override));
    MOCK_METHOD(bool, isValidMenuChoice, (const char* input), (override));
};
