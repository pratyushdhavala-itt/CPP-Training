#include <iostream>

#include "savings_account.h"

double SavingsAccount::getBalance() const {
    std::cout << "[SavingsAccount] Checking balance..." << std::endl;
    return Account::getBalance();
}

void SavingsAccount::setBalance(double balance) {
    std::cout << "[SavingsAccount] Updating balance to " << balance << std::endl;
    Account::setBalance(balance);
}

Account::AccountType SavingsAccount::getAccountType() const {
    return SAVINGS_ACCOUNT;
}