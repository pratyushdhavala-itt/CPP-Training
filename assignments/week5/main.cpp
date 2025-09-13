#include <iostream>

#include "authenticator.h"
#include "bank.h"
#include "constants.h"
#include "input_validation.h"
#include "account.h"
#include "input_output.h"


int main() {

    Bank& bank = Bank::getBankInstance();

    while (true) {

        std::string userID;
        std::string attemptedPassword;

        std::cout << PRINT_ENTER_USER_ID;
        std::getline(std::cin, userID);
        if (!InputValidation::isValidUserID(userID)) {
            std::cout << PRINT_INVALID_USER_FORMAT << std::endl;
            continue;
        }

        std::cout << PRINT_ENTER_PASSWORD;
        std::getline(std::cin, attemptedPassword);
        if (!InputValidation::isValidPassword(attemptedPassword)) {
            std::cout << PRINT_INVALID_PASSWORD_FORMAT << std::endl;
            continue;
        }

        bank.login(userID, attemptedPassword);

        if (bank.getCurrentUserState() != Bank::AUTHENTICATED) {
            std::cout << bank.getAuthenticationError() << std::endl;
            continue;
        }
        std::cout << bank.getLoginMessage() << std::endl;
        if (bank.getCurrentUserType() == User::CUSTOMER) {
            performCustomerBankOperation(bank);
        } else if (bank.getCurrentUserType() == User::ADMIN) {
            performAdminBankOperation(bank);
        }
    }   
}

