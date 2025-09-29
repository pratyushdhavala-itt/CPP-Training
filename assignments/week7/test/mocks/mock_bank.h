#ifndef MOCKBANK_H
#define MOCKBANK_H

#include <gmock/gmock.h>
#include "bank.h"

class MockBank : public Bank {
public:

    MockBank() : Bank(nullptr) {}


    MOCK_METHOD(void, login, (std::string& userID, std::string& attemptedPassword), (override));
    MOCK_METHOD(std::string, getLoginMessage, (), (const, override));
    MOCK_METHOD(std::string, getErrorMessage, (), (const, override));
    MOCK_METHOD(Authenticator::AuthenticationErrorState, getAuthenticationErrorState, (), (override));
    MOCK_METHOD(void, setAuthenticationErrorState, (Authenticator::AuthenticationErrorState), (override));
    MOCK_METHOD(User::UserType, getUserType, (), (const, override));
    MOCK_METHOD(void, setCurrentUser, (User* user), (override));
    MOCK_METHOD(User*, getCurrentUser, (), (override));
    MOCK_METHOD(void, logout, (), (override));

    MOCK_METHOD(void, showMenu, (), (const, override));

    MOCK_METHOD(TransactionState, getCurrentTransactionState, (), (const, override));
    MOCK_METHOD(void, setCurrentTransactionState, (TransactionState), (override));
    MOCK_METHOD(Account*, getCustomerAccount, (), (const, override));
    MOCK_METHOD(double, getCustomerBalance, (), (const, override));
    MOCK_METHOD(void, setCustomerBalance, (double), (override));
    MOCK_METHOD(void, deposit, (double), (override));
    MOCK_METHOD(void, withdraw, (double), (override));
    MOCK_METHOD(void, transfer, (long destAccountNo, double amount), (override));
    MOCK_METHOD(std::string, getAccountMiniStatement, (), (const, override));
    MOCK_METHOD(std::string, getAccountFullStatement, (), (const, override));

    MOCK_METHOD(void, reset, (), (override));
    MOCK_METHOD(User*, createUser, (User::UserDetails& userDetails, Account::AccountType accountType), (override));
    MOCK_METHOD(User*, getUserById, (const std::string& userID), (const, override));
    MOCK_METHOD(void, addUser, (User* newUser), (override));
    MOCK_METHOD(void, deleteUser, (User::UserDetails& userDetails), (override));
    MOCK_METHOD(int, getUserIndex, (std::string& userID), (override));
    MOCK_METHOD(std::string, getAllCustomerDetails, (), (const, override));
    MOCK_METHOD(Account*, getAccountByNumber, (long accountNumber), (override));

    MOCK_METHOD(std::string, helperGetAccountStatement, (int limit), (const, override));
    MOCK_METHOD(void, recordTransaction, (double amount, Transaction::TransactionType transactionType, double newBalance), (override));
    MOCK_METHOD(void, recordTransaction, (long otherAccNo, Account* currentTransactionAccount, double amount, Transaction::TransactionType transactionType, double newBalance), (override));
};

#endif 
