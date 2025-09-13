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
    enum AuthenticationState {
        AUTHENTICATED = 1,
        UNAUTHENTICATED = 2,
    };


private:

    Bank();

    int userCount;
    static const int MAX_AMOUNT = 99999999;
    User** users;
    Authenticator authenticator;
    User* currentUser;
    Customer* currentCustomer;
    Admin* currentAdmin;
    AuthenticationState currentAuthenticationState;
    TransactionState currentTransactionState;
    Authenticator::AuthenticationErrorState currentAuthenticationErrorState;


    int getUserIndex(std::string& userID);
    Customer* findUserByAccountNo(long accountNumber);
    std::string helperGetAccountStatement(int limit);
    void recordTransaction(Customer* customer, double amount, Transaction::TransactionType transactionType);
    void recordTransaction(Customer* customer, double amount, Transaction::TransactionType transactionType, long destinationAccNo);
    void setCustomerOrAdmin();

public:

    static Bank& getBankInstance();

    User* findUserById(std::string& userID);
    void login(std::string& userID, std::string& attemptedPassword);
    void showMenu();
    AuthenticationState getCurrentUserState();
    User::UserType getCurrentUserType();
    TransactionState getCurrentTransactionState();
    std::string getAuthenticationError();
    void logout();
    std::string getLoginMessage();

    void addUser(std::string& userFirstName, std::string& userLastName, std::string& userID, std::string& userPassword, Account::AccountType accountType);
    void deleteUser(std::string& userID);
    std::string getAllCustomerDetails();

    double getCustomerBalance();
    void deposit(double amount);
    void withdraw(double amount);
    void transfer(long destAccountNo, double amount);
    std::string getAccountMiniStatement();
    std::string getAccountFullStatement();

    Bank(const Bank&) = delete;
    Bank& operator=(const Bank&) = delete;
    ~Bank();
};

#endif