#include <iostream>

#include "account.h"

int Account::accountCount = 0;

Account::Account() : balance{INITIAL_BALANCE}, transactions{nullptr}, transactionCount{0} {
    accountCount++;
    accountNumber = DEFAULT_ACC_NO + accountCount;
}

void Account::addTransaction(Transaction* transaction) {
    transactionCount++;
    transactions = (Transaction**) realloc(transactions, transactionCount * sizeof(Transaction*));
    *(transactions + transactionCount - 1) = transaction;
}

Transaction** Account::getAllTransactions() const {
    return transactions;
}

double Account::getBalance() const {
    return balance;
}

void Account::setBalance(double amount) {
    balance = amount;
}

long Account::getAccountNumber() const {
    return accountNumber;
}

int Account::getTransactionCount() const {
    return transactionCount;
}
Account::~Account() {
    for (int index = 0; index < transactionCount; index++) {
        delete *(transactions + index);
    }
    free(transactions);
}

Account::AccountType Account::getAccountType() const {
    return accountType;
}