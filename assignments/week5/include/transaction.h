#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "date_time.h"

class Transaction {

public:
    enum TransactionType {
        DEPOSIT_TRANSACTION = 1,
        WITHDRAW_TRANSACTION = 2,
        SENT_TRANSFER_TRANSACTION = 3,
        RECD_TRANSFER_TRANSACTION = 4,
    };

private:
    
    long transactionID;
    double closingBalance;
    double transactionAmount;
    TransactionType transactionType;
    DateTime timeStamp;
    double postTransactionBalance;
    long destinationAccountNo;
    static const int BASE_TRANSACTION_ID = 1000;

public:

    static int transactionCount;

    Transaction(double transactionAmount, TransactionType transactionType, double postTransactionBalance);
    Transaction(double transactionAmount, TransactionType transactionType, double postTransactionBalance, long destinationAccountNo);

    std::string toString();
    std::string transactionTypeToString(TransactionType transactionType);
};

#endif