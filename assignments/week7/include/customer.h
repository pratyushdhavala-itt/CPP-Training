#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "user.h"
#include "account.h"

class Customer : public User {

public:

    enum CustomerBankOperations {

        BALANCE = 1,
        DEPOSIT = 2,
        WITHDRAW = 3,
        TRANSFER = 4,
        MINI_STATEMENT = 5,
        FULL_STATEMENT = 6,
    };

private:

    Account* bankAccount;

public:

    Customer(UserDetails customerDetails);
    virtual Account* getAccount() override;
    virtual void showMenu() const override;
    virtual std::string toString() override;
    virtual void createAccount(Account* newAccount);
    virtual ~Customer();
};

#endif