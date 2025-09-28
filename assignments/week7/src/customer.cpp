#include <iostream>

#include "customer.h"
#include "constants.h"
#include "savings_account.h"
#include "current_account.h"


Customer::Customer(UserDetails customerDetails) 
    : User(customerDetails, CUSTOMER), bankAccount{nullptr} {

}

void Customer::createAccount(Account* newAccount) {
    bankAccount = newAccount;
}
      
void Customer::showMenu() const {
    std::cout << PRINT_CUSTOMER_MENU << std::endl;
}

Account* Customer::getAccount() {
    return bankAccount;
}

std::string Customer::toString() {
    return std::string(PRINT_LINE_SEPARATOR) + '\n' +
           PRINT_OUTPUT_CUSTOMER_NAME + getUserFullName() + '\n' +
           PRINT_OUTPUT_CUSTOMER_ID + getUserID() + '\n' +
           PRINT_OUTPUT_CUSTOMER_ACC_ID + std::to_string(getAccount()->getAccountNumber()) + '\n' +
           PRINT_OUTPUT_CUSTOMER_ACC_BALANCE + std::to_string(getAccount()->getBalance());

}

Customer::~Customer() {

    if (bankAccount) {
        delete bankAccount;
    }
    
}