#include <iostream>

#include "authenticator.h"
#include "bank.h"
#include "constants.h"
#include "input_validation.h"
#include "account.h"
#include "input_output.h"


int main() {

    Authenticator auth;
    Bank& bank = Bank::getBankInstance(&auth);
    InputValidation inputValidation;

    while (true) {

        std::string userID;
        std::string attemptedPassword;

        std::cout << PRINT_ENTER_USER_ID;
        std::getline(std::cin, userID);
        if (!inputValidation.isValidUserID(userID)) {
            std::cout << PRINT_INVALID_USER_FORMAT << std::endl;
            continue;
        }

        std::cout << PRINT_ENTER_PASSWORD;
        std::getline(std::cin, attemptedPassword);
        if (!inputValidation.isValidPassword(attemptedPassword)) {
            std::cout << PRINT_INVALID_PASSWORD_FORMAT << std::endl;
            continue;
        }

        bank.login(userID, attemptedPassword);

        if (bank.getAuthenticationErrorState() != Authenticator::NO_ERROR) {
            
            std::cout << bank.getErrorMessage() << std::endl;
            continue;
        }
        std::cout << bank.getLoginMessage() << std::endl;
        if (bank.getUserType() == User::CUSTOMER) {
            performCustomerBankOperation(bank, inputValidation);
        } else if (bank.getUserType() == User::ADMIN) {
            performAdminBankOperation(bank, inputValidation);
        }
    }   
}