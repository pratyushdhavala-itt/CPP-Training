#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H

#include "account.h"

class SavingsAccount : public Account {

    double getBalance() const override;
    void setBalance(double amount) override;
    Account::AccountType getAccountType() const override;
};

#endif