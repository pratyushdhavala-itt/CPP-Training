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

public:

    Account();

    double getBalance() const;
    void setBalance(double balance);
    long getAccountNumber() const;
    void addTransaction(Transaction* transaction);
    Transaction** getAllTransactions() const;
    int getTransactionCount() const;

    ~Account();
};

#endif