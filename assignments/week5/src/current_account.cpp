#include <iostream>

#include "current_account.h"

double CurrentAccount::getBalance() const {
    std::cout << "[CurrentAccount] Retrieving balance with overdraft check..." << std::endl;
    return Account::getBalance();
}

void CurrentAccount::setBalance(double balance) {
    std::cout << "[CurrentAccount] Setting balance (fees may apply): " << balance << std::endl;
    Account::setBalance(balance);
}

Account::AccountType CurrentAccount::getAccountType() const {
    return CURRENT_ACCOUNT;
}