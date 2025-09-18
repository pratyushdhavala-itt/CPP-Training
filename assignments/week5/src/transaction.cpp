#include <iostream>
#include <ctime>

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
    postTransactionBalance{postTransactionBalance} {

}

std::string Transaction::getTimeStamp() {

    std::time_t timeNow = std::time(nullptr);
    std::tm* localTime = std::localtime(&timeNow);

    int day = localTime->tm_mday;
    int month = localTime->tm_mon + 1;
    int year = localTime->tm_year + 1900;
    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;

    return std::to_string(day) + PRINT_SLASH +
           std::to_string(month) + PRINT_SLASH +
           std::to_string(year) + PRINT_SPACE +
           std::to_string(hour) + PRINT_COLON +
           std::to_string(minute) + PRINT_COLON +
           std::to_string(second);
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
        PRINT_OUTPUT_TRANSACTION_TIMESTAMP + getTimeStamp() + '\n' +
        PRINT_OUTPUT_TRANSACTION_ID + std::to_string(transactionID) + '\n' + 
        PRINT_OUTPUT_TRANSACTION_TYPE + transactionTypeToString + '\n' +
        PRINT_OUTPUT_TRANSACTION_AMOUNT + std::to_string(transactionAmount) + '\n' +
        PRINT_OUTPUT_TRANSACTION_BALANCE + std::to_string(postTransactionBalance);
}