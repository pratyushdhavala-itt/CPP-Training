#include <iostream>

#include "customer.h"
#include "constants.h"
#include "savings_account.h"
#include "current_account.h"


Customer::Customer(std::string userFirstName, std::string userLastName, std::string userID, std::string userPassword, Account::AccountType accountType) 
    : User(userFirstName, userLastName, userID, userPassword, CUSTOMER), 
    bankAccount{nullptr} {

        if (accountType == Account::SAVINGS_ACCOUNT) {
            bankAccount = new SavingsAccount();
        } else {
            bankAccount = new CurrentAccount();
        }

}
void Customer::showMenu() const {
    std::cout << PRINT_CUSTOMER_MENU << std::endl;
}

Account* Customer::getCustomerAccount() {
    return bankAccount;
}

std::string Customer::toString() {
    return std::string(PRINT_LINE_SEPARATOR) + '\n' +
           PRINT_OUTPUT_CUSTOMER_NAME + getUserFullName() + '\n' +
           PRINT_OUTPUT_CUSTOMER_ID + getUserID() + '\n' +
           PRINT_OUTPUT_CUSTOMER_ACC_ID + std::to_string(getCustomerAccount()->getAccountNumber()) + '\n' +
           PRINT_OUTPUT_CUSTOMER_ACC_BALANCE + std::to_string(getCustomerAccount()->getBalance());

}

Customer::~Customer() {
    delete bankAccount;
}