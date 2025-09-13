#include <iostream>

#include "transaction.h"
#include "constants.h"

int Transaction::transactionCount = 0;

Transaction::Transaction(double transactionAmount, TransactionType transactionType, double postTransactionBalance) 
    : Transaction(transactionAmount, transactionType, postTransactionBalance, 0) {}

Transaction::Transaction(double transactionAmount, TransactionType transactionType, double postTransactionBalance, long destinationAccountNo) :
    transactionAmount{transactionAmount}, 
    transactionType{transactionType}, 
    destinationAccountNo{destinationAccountNo} , 
    transactionID{BASE_TRANSACTION_ID + (++transactionCount)},
    timeStamp{DateTime()},
    postTransactionBalance{postTransactionBalance} {

}

std::string Transaction::toString() {

    std::string transactionTypeToString;
    switch(transactionType) {
        case DEPOSIT_TRANSACTION:
            transactionTypeToString = PRINT_DEPOSIT;
            break;
        
        case WITHDRAW_TRANSACTION:
            transactionTypeToString = PRINT_WITHDRAWAL;
            break;

        case SENT_TRANSFER_TRANSACTION:
            transactionTypeToString = PRINT_SENT_TRANSFER + std::to_string(destinationAccountNo);
            break;

        case RECD_TRANSFER_TRANSACTION:
            transactionTypeToString = PRINT_RECD_TRANSFER + std::to_string(destinationAccountNo);
            break;
        default:
            break;
    }

    return std::string(PRINT_LINE_SEPARATOR) + '\n' +
        PRINT_OUTPUT_TRANSACTION_TIMESTAMP + timeStamp.toString() + '\n' +
        PRINT_OUTPUT_TRANSACTION_ID + std::to_string(transactionID) + '\n' + 
        PRINT_OUTPUT_TRANSACTION_TYPE + transactionTypeToString + '\n' +
        PRINT_OUTPUT_TRANSACTION_AMOUNT + std::to_string(transactionAmount) + '\n' +
        PRINT_OUTPUT_TRANSACTION_BALANCE + std::to_string(postTransactionBalance);
}