#include <iostream>

#include "bank.h"
#include "constants.h"
#include "user.h"
#include "customer.h"
#include "transaction.h"
#include "authenticator.h"

Bank::Bank() 
    : userCount{1}, 
    currentAdmin{nullptr},
    authenticator{Authenticator()},
    authenticationErrorState{Authenticator::NO_ERROR},
    bankAccount{nullptr} {

    

    std::cout << PRINT_WELCOME_BANK << std::endl;
}

Bank& Bank::getBankInstance() {
    static Bank bank;
    return bank;
}

void Bank::showMenu() const {
    authenticator.getAuthenticatedUser()->showMenu();
}

double Bank::getCustomerBalance() const {
    return bankAccount->getBalance();
}

Bank::TransactionState Bank::getCurrentTransactionState() const {
    return currentTransactionState;
}

void Bank::login(std::string& userID, std::string& attemptedPassword) {

    Authenticator::AuthenticationState authenticationState = authenticator.authenticate(userID, attemptedPassword);
    
    if (authenticationState == Authenticator::AUTHENTICATED) {
        User* tempUser = authenticator.getAuthenticatedUser();
        if (tempUser->getUserType() == User::CUSTOMER) {
            Customer* customer = dynamic_cast<Customer*>(tempUser);
            bankAccount = customer->getCustomerAccount();
            userType = User::CUSTOMER;
        } else {
            currentAdmin = dynamic_cast<Admin*>(tempUser);
            userType = User::ADMIN;
        }
    } else {
        authenticationErrorState = authenticator.getAuthenticationErrorState();
    }

}

void Bank::logout() {
    authenticator.unAuthenticate();
    authenticationErrorState = Authenticator::NO_ERROR;
    currentAdmin = nullptr;
}

Authenticator::AuthenticationErrorState Bank::getAuthenticationErrorState() {
    return authenticationErrorState;
}


void Bank::addUser(std::string& userFirstName, std::string& userLastName, std::string& userID, std::string& userPassword, Account::AccountType accountType) {

    authenticator.addUser(userFirstName, userLastName, userID, userPassword, accountType);
    Customer* tempCustomer = dynamic_cast<Customer*>(authenticator.findUserById(userID));
    std::cout << "Created user: " + userID << "\nAccount Number: " + std::to_string(tempCustomer->getCustomerAccount()->getAccountNumber()) << std::endl;
    
}

void Bank::deleteUser(std::string& userID) {

    authenticator.deleteUser(userID);
}

std::string Bank::getAllCustomerDetails() const {

    return authenticator.getAllCustomerDetails();
}

void Bank::deposit(double amount) {

    if (amount > MAX_AMOUNT) {
        currentTransactionState = FAILURE;
        return;
    }

    double newBalance = getCustomerBalance() + amount;
    bankAccount->setBalance(newBalance);
    currentTransactionState = SUCCESS;
    recordTransaction(this->bankAccount, amount, Transaction::DEPOSIT_TRANSACTION);
}

void Bank::withdraw(double amount) {

    double currentBalance = getCustomerBalance();
    if (amount > currentBalance) {
        currentTransactionState = FAILURE;
        return;
    }

    double newBalance = currentBalance - amount;
    bankAccount->setBalance(newBalance);
    currentTransactionState = SUCCESS;
    recordTransaction(this->bankAccount, amount, Transaction::WITHDRAW_TRANSACTION);
}

std::string Bank::getLoginMessage() const {
    return authenticator.getLoginMessage();
}

void Bank::transfer(long destAccountNo, double amount) {

    if (amount > MAX_AMOUNT || amount > getCustomerBalance()) {
        currentTransactionState = FAILURE;
        return;
    }

    Account* destinationAccount = authenticator.findAccountByNumber(destAccountNo);

    if (destinationAccount) {

        double newBalance = destinationAccount->getBalance() + amount;
        destinationAccount->setBalance(newBalance);
        recordTransaction(destinationAccount, amount, Transaction::RECD_TRANSFER_TRANSACTION, bankAccount->getAccountNumber());
        bankAccount->setBalance(getCustomerBalance() - amount);
        currentTransactionState = SUCCESS;
        recordTransaction(bankAccount, amount, Transaction::SENT_TRANSFER_TRANSACTION, destAccountNo);
    
    } else {
        std::cout << PRINT_DEST_ACC_DOES_NOT_EXIST << std::endl; 
        currentTransactionState = FAILURE;
    }
}

std::string Bank::helperGetAccountStatement(int limit) const {
    Transaction** transactions = bankAccount->getAllTransactions();
    std::string combinedTransactions;
    for (int transactionIndex = limit - 1; transactionIndex >= 0; transactionIndex--) {
        combinedTransactions += (*(transactions + transactionIndex))->toString();
    }
    return combinedTransactions;
}

std::string Bank::getAccountFullStatement() const {
    return helperGetAccountStatement(bankAccount->getTransactionCount());
}

std::string Bank::getAccountMiniStatement() const {
    int transactionCount = bankAccount->getTransactionCount();
    int limit = (transactionCount > 10) ? 10 : transactionCount;
    return helperGetAccountStatement(limit);
}

void Bank::recordTransaction(Account* bankAccount, double amount, Transaction::TransactionType transactionType) {
    Transaction* newTransaction = new Transaction(amount, transactionType, bankAccount->getBalance());
    bankAccount->addTransaction(newTransaction);
}

void Bank::recordTransaction(Account* bankAccount, double amount, Transaction::TransactionType transactionType, long destinationAccNo) {
    Transaction* newTransaction = new Transaction(amount, transactionType, bankAccount->getBalance(), destinationAccNo);
    bankAccount->addTransaction(newTransaction);
}

Bank::~Bank() {

}

User::UserType Bank::getUserType() const {
    return userType;
}

std::string Bank::getErrorMessage() const {
    std::string authenticationError;
    switch(authenticationErrorState) {
        case Authenticator::WRONG_PASSWORD: {
            authenticationError = PRINT_WRONG_PASSWORD;
            break;
        }
        case Authenticator::WRONG_USER_NAME: {
            authenticationError = PRINT_WRONG_USER_NAME;
            break;
        }
    }
    return authenticationError;
}
