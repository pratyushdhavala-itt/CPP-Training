#ifndef CURRENT_ACCOUNT_H
#define CURRENT_ACCOUNT_H

#include "account.h"

class CurrentAccount : public Account {
    double getBalance() const override;
    void setBalance(double amount) override;
    Account::AccountType getAccountType() const override;

};

#endif