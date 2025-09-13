#include <iostream>

#include "bank.h"
#include "constants.h"
#include "user.h"
#include "customer.h"
#include "transaction.h"
#include "authenticator.h"

Bank::Bank() 
    : userCount{1}, 
    currentUser{nullptr},
    currentAdmin{nullptr},
    currentCustomer{nullptr},
    authenticator{Authenticator()},
    users{(User**) malloc(sizeof(User*))},
    currentAuthenticationState{UNAUTHENTICATED}, 
    currentAuthenticationErrorState{Authenticator::NO_ERROR} {

    Admin* admin = new Admin();
    *(users) = admin;

    std::cout << PRINT_WELCOME_BANK << std::endl;
}

Bank& Bank::getBankInstance() {
    static Bank bank;
    return bank;
}

void Bank::setCustomerOrAdmin() {
    if (currentUser->getUserType() == User::ADMIN) {
        currentAdmin = dynamic_cast<Admin*>(currentUser);
    } else if (currentUser->getUserType() == User::CUSTOMER) {
        currentCustomer = dynamic_cast<Customer*>(currentUser);
    }
}

void Bank::login(std::string& userID, std::string& attemptedPassword) {
    User* tempUser = findUserById(userID);
    if (tempUser) {
        authenticator.authenticate(tempUser, attemptedPassword);
        if (authenticator.getAuthenticatedUser()) {
            currentUser = authenticator.getAuthenticatedUser();
            setCustomerOrAdmin();
            currentAuthenticationState = AUTHENTICATED;
            currentAuthenticationErrorState = Authenticator::NO_ERROR;
        } else {
            currentAuthenticationErrorState = Authenticator::WRONG_PASSWORD;
        }
    } else {
        currentAuthenticationErrorState = Authenticator::WRONG_USER_NAME;
    }
}


Bank::AuthenticationState Bank::getCurrentUserState() {
    return currentAuthenticationState;
}

std::string Bank::getLoginMessage() {
    return PRINT_LOGIN + currentUser->getUserID() + PRINT_LOGIN_WELCOME + currentUser->getUserFullName() + PRINT_NEXT_LINE;
}

User::UserType Bank::getCurrentUserType() {
    return currentUser->getUserType();
}

void Bank::showMenu() {
    currentUser->showMenu();
}

User* Bank::findUserById(std::string& userID) {
    for (int index = 0; index < userCount; index++) {
        if ((*(users + index))->getUserID() == userID) {
            return *(users + index);
        }
    }
    return nullptr;
}

int Bank::getUserIndex(std::string& userID) {
    for (int i = 0; i < userCount; i++) {
        if ((*(users + i))->getUserID() == userID) {
            return i;
        }
    }
    return -1;
}

void Bank::addUser(std::string& userFirstName, std::string& userLastName, std::string& userID, std::string& userPassword, Account::AccountType accountType) {
    userCount++;
    users = (User**) realloc(users, userCount * sizeof(User*));
    if (accountType != Account::ADMIN_ACCOUNT) {
        *(users + (userCount - 1)) = new Customer(userFirstName, userLastName, userID, userPassword, accountType);
    } else {
        *(users + (userCount - 1)) = new Admin(userFirstName, userLastName, userID, userPassword);
    }
    
}

void Bank::deleteUser(std::string& userID) {

    if (currentUser->getUserID() == userID) {
        std::cout << PRINT_CANNOT_DELETE_CURRENT_USER << std::endl;
        currentTransactionState = FAILURE;
        return;
    }

    int deleteUserIndex = getUserIndex(userID);
    if (deleteUserIndex == -1) {
        std::cout << PRINT_USER_DOES_NOT_EXIST << std::endl;
        currentTransactionState = FAILURE;
        return;
    }

    delete *(users + deleteUserIndex);
    for (int index = deleteUserIndex; index < userCount - 1; index++) {
        *(users + index) = *(users + index + 1);
    }

    userCount--;
    if (userCount > 0) {
        users = (User**) realloc(users, userCount * sizeof(User*));
    } else {
        free(users);
        users = nullptr;
    }
    currentTransactionState = SUCCESS;
}

std::string Bank::getAllCustomerDetails() {
    std::string combinedCustomerDetails;
    for (int index = 0; index < userCount; index++) {
        Customer* tempCustomer = dynamic_cast<Customer*>(*(users + index));
        if (tempCustomer) {
            combinedCustomerDetails += tempCustomer->toString();
        }
    }
    if (combinedCustomerDetails.empty()) combinedCustomerDetails = PRINT_NO_CUSTOMER;
    return combinedCustomerDetails;
}

double Bank::getCustomerBalance() {
    return currentCustomer->getCustomerAccount().getBalance();
}

void Bank::deposit(double amount) {

    if (amount > MAX_AMOUNT) {
        currentTransactionState = FAILURE;
        return;
    }

    double newBalance = getCustomerBalance() + amount;
    currentCustomer->getCustomerAccount().setBalance(newBalance);
    currentTransactionState = SUCCESS;
    recordTransaction(currentCustomer, amount, Transaction::DEPOSIT_TRANSACTION);
}

void Bank::withdraw(double amount) {

    double currentBalance = getCustomerBalance();
    if (amount > currentBalance) {
        currentTransactionState = FAILURE;
        return;
    }

    double newBalance = currentBalance - amount;
    currentCustomer->getCustomerAccount().setBalance(newBalance);
    currentTransactionState = SUCCESS;
    recordTransaction(currentCustomer, amount, Transaction::WITHDRAW_TRANSACTION);
}

void Bank::transfer(long destAccountNo, double amount) {

    double sendingCustomerBalance = getCustomerBalance();
    if (amount > MAX_AMOUNT || amount > sendingCustomerBalance) {
        currentTransactionState = FAILURE;
        return;
    }

    Customer* recevingCustomer = findUserByAccountNo(destAccountNo);

    if (recevingCustomer) {

        double newBalance = recevingCustomer->getCustomerAccount().getBalance() + amount;
        recevingCustomer->getCustomerAccount().setBalance(newBalance);
        currentCustomer->getCustomerAccount().setBalance(sendingCustomerBalance - amount);
        currentTransactionState = SUCCESS;
        recordTransaction(currentCustomer, amount, Transaction::SENT_TRANSFER_TRANSACTION, destAccountNo);
        recordTransaction(recevingCustomer, amount, Transaction::RECD_TRANSFER_TRANSACTION, currentCustomer->getCustomerAccount().getAccountNumber());
    
    } else {
        std::cout << PRINT_DEST_ACC_DOES_NOT_EXIST << std::endl; 
        currentTransactionState = FAILURE;
    }
}

Customer* Bank::findUserByAccountNo(long accountNumber) {
    Customer* customer = nullptr;
    for (int index = 0; index < userCount; index++) {
        Customer* tempCustomer = dynamic_cast<Customer*>(*(users + index));
        if (tempCustomer) {
            if (tempCustomer->getCustomerAccount().getAccountNumber() == accountNumber) {
                customer = tempCustomer;
                break;
            }
        }
    }
    return customer;
}

std::string Bank::helperGetAccountStatement(int limit) {
    Customer* customer = dynamic_cast<Customer*>(currentUser);
    Transaction** transactions = customer->getCustomerAccount().getAllTransactions();
    std::string combinedTransactions;
    for (int index = limit - 1; index >= 0; index--) {
        combinedTransactions += (*(transactions + index))->toString();
    }
    return combinedTransactions;
}

std::string Bank::getAccountFullStatement() {
    return helperGetAccountStatement(currentCustomer->getCustomerAccount().getTransactionCount());
}

std::string Bank::getAccountMiniStatement() {
    int transactionCount = currentCustomer->getCustomerAccount().getTransactionCount();
    int limit = (transactionCount > 10) ? 10 : transactionCount;
    return helperGetAccountStatement(limit);
}

Bank::TransactionState Bank::getCurrentTransactionState() {
    return currentTransactionState;
}

void Bank::recordTransaction(Customer* customer, double amount, Transaction::TransactionType transactionType) {
    Transaction* newTransaction = new Transaction(amount, transactionType, customer->getCustomerAccount().getBalance());
    customer->getCustomerAccount().addTransaction(newTransaction);
}

void Bank::recordTransaction(Customer* customer, double amount, Transaction::TransactionType transactionType, long destinationAccNo) {
    Transaction* newTransaction = new Transaction(amount, transactionType, customer->getCustomerAccount().getBalance(), destinationAccNo);
    customer->getCustomerAccount().addTransaction(newTransaction);
}

Bank::~Bank() {
    for (int index = 0; index < userCount; index++) {
        delete *(users + index);
    }
    free(users);
}

void Bank::logout() {
    authenticator.unAuthenticate();
    currentUser = nullptr;
    currentAuthenticationState = UNAUTHENTICATED;
    currentAuthenticationErrorState = Authenticator::NO_ERROR;
}

std::string Bank::getAuthenticationError() {
    std::string authenticationError;
    switch(currentAuthenticationErrorState) {
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