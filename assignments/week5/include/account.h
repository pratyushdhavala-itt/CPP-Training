#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "transaction.h"

class Account {

public:
    enum AccountConstants {
        INITIAL_BALANCE = 10000,
        DEFAULT_ACC_NO = 1000,
    };

    enum AccountType {
        SAVINGS_ACCOUNT = 1,
        CURRENT_ACCOUNT = 2,
        ADMIN_ACCOUNT = 3,
    };
    
private:
    static int accountCount;
    long accountNumber;
    double balance;
    Transaction** transactions;
    int transactionCount;
    AccountType accountType;

public:

    Account();

    virtual double getBalance() const = 0;
    virtual void setBalance(double balance) = 0;
    virtual long getAccountNumber() const;
    virtual void addTransaction(Transaction* transaction);
    virtual Transaction** getAllTransactions() const;
    virtual int getTransactionCount() const;
    virtual AccountType getAccountType() const = 0;

    ~Account();
};

#endif