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

    Customer(std::string userFirstName, std::string userLastName, std::string userID, std::string userPassword, Account::AccountType accountType);

    Account* getCustomerAccount();
    void showMenu() const override;
    std::string toString();

    ~Customer();
};

#endif