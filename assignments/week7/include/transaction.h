#ifndef TRANSACTION_H
#define TRANSACTION_H

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
    double postTransactionBalance;
    long destinationAccountNo;
    static const int BASE_TRANSACTION_ID = 99063000;

public:

    static int transactionCount;

    Transaction(double transactionAmount, TransactionType transactionType, double postTransactionBalance);
    Transaction(long destinationAccountNo, double transactionAmount, TransactionType transactionType, double postTransactionBalance);

    std::string getTimeStamp();
    std::string toString();
};

#endif