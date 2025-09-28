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
        DEFAULT_STATE = 0,
        SUCCESS = 1,
        FAILURE = 2,
    };


private:

    Bank(Authenticator* auth);

    User** allUsers;
    User* currentUser;
    int userCount;
    Authenticator* authenticator;
    TransactionState currentTransactionState;
    Authenticator::AuthenticationErrorState authenticationErrorState;
    User::UserType userType;

    virtual std::string helperGetAccountStatement(int limit) const;
    virtual void recordTransaction(double amount, Transaction::TransactionType transactionType, double newBalance);
    virtual void recordTransaction(long otherAccNo, Account* currentTransactionAccount, double amount, Transaction::TransactionType transactionType, double newBalance);

public:
    static const int MAX_AMOUNT = 99999999;


    static Bank& getBankInstance(Authenticator* auth);

    virtual void login(std::string& userID, std::string& attemptedPassword);
    virtual std::string getLoginMessage() const;
    virtual std::string getErrorMessage() const;
    virtual Authenticator::AuthenticationErrorState getAuthenticationErrorState();
    virtual void setAuthenticationErrorState(Authenticator::AuthenticationErrorState authenticationErrorState);
    virtual TransactionState getCurrentTransactionState() const;
    virtual void setCurrentTransactionState(TransactionState currentTransactionState);
    virtual User::UserType getUserType() const;
    virtual void showMenu() const;
    virtual void setCurrentUser(User* user);
    virtual User* getCurrentUser();
    virtual void logout();

    virtual Account* getCustomerAccount() const;
    virtual double getCustomerBalance() const;
    virtual void setCustomerBalance(double amount);
    virtual void deposit(double amount);
    virtual void withdraw(double amount);
    virtual void transfer(long destAccountNo, double amount);
    virtual std::string getAccountMiniStatement() const;
    virtual std::string getAccountFullStatement() const;

    virtual void reset();

    Bank(const Bank&) = delete;
    Bank& operator=(const Bank&) = delete;
    ~Bank();

    virtual User* createUser(User::UserDetails& userDetails, Account::AccountType accountType);
    virtual User* getUserById(const std::string& userID) const;
    virtual void addUser(User* newUser);
    virtual void deleteUser(User::UserDetails& userDetails);
    virtual int getUserIndex(std::string& userID);
    virtual std::string getAllCustomerDetails() const;
    virtual Account* getAccountByNumber(long accountNumber);
};

#endif
