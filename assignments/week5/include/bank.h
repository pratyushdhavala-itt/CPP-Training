#ifndef BANK_H
#define BANK_H

#include <iostream>

#include "authenticator.h"
#include "user.h"
#include "admin.h"
#include "customer.h"

class Bank {

public:

    enum TransactionState {
        SUCCESS = 1,
        FAILURE = 2,
    };


private:

    Bank();

    int userCount;
    static const int MAX_AMOUNT = 99999999;
    Authenticator authenticator;
    Admin* currentAdmin;
    TransactionState currentTransactionState;
    Authenticator::AuthenticationErrorState authenticationErrorState;
    Account* bankAccount;
    User::UserType userType;

    int getUserIndex(std::string& userID);
    std::string helperGetAccountStatement(int limit) const;
    void recordTransaction(Account* bankAccount, double amount, Transaction::TransactionType transactionType);
    void recordTransaction(Account* bankAccount, double amount, Transaction::TransactionType transactionType, long destinationAccNo);
    
public:

    static Bank& getBankInstance();

    void login(std::string& userID, std::string& attemptedPassword);
    std::string getLoginMessage() const;
    std::string getErrorMessage() const;
    Authenticator::AuthenticationErrorState getAuthenticationErrorState();
    TransactionState getCurrentTransactionState() const;
    User::UserType getUserType() const;
    void showMenu() const;
    void logout();

    void addUser(std::string& userFirstName, std::string& userLastName, std::string& userID, std::string& userPassword, Account::AccountType accountType);
    void deleteUser(std::string& userID);
    std::string getAllCustomerDetails() const;

    double getCustomerBalance() const;
    void deposit(double amount);
    void withdraw(double amount);
    void transfer(long destAccountNo, double amount);
    std::string getAccountMiniStatement() const;
    std::string getAccountFullStatement() const;

    Bank(const Bank&) = delete;
    Bank& operator=(const Bank&) = delete;
    ~Bank();
};

#endif
