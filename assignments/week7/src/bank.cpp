#include <iostream>

#include "bank.h"
#include "constants.h"
#include "user.h"
#include "customer.h"
#include "transaction.h"
#include "authenticator.h"
#include "savings_account.h"
#include "current_account.h"

Bank::Bank(Authenticator* auth)
    : userCount{0},
    authenticator(auth),
    currentUser(nullptr),
    allUsers{(User**) malloc (sizeof(User*))},
    authenticationErrorState(Authenticator::NO_ERROR),
    currentTransactionState(DEFAULT_STATE),
    userType{User::DEFAULT_STATE} {

        User::UserDetails defaultAdminDetails{PRINT_DEFAULT_ADMIN_ID, PRINT_DEFAULT_ADMIN_PASSWORD, PRINT_DEFAULT_ADMIN_NAME, PRINT_DEFAULT_ADMIN_LAST_NAME};
        User* defaultAdmin = createUser(defaultAdminDetails, Account::ADMIN_ACCOUNT);
        addUser(defaultAdmin);
        // setCurrentUser(getUserById(std::string(PRINT_DEFAULT_ADMIN_ID)));
        setCurrentUser(nullptr);
        std::cout << PRINT_WELCOME_BANK << std::endl;
}

Bank& Bank::getBankInstance(Authenticator* auth) {
    static Bank bank(auth);
    return bank;
}

void Bank::setCurrentUser(User* user) {

    currentUser = user;
    if (user) {
        userType = currentUser->getUserType();
    }
    
}

void Bank::showMenu() const {
    currentUser->showMenu();
}

double Bank::getCustomerBalance() const {
    Account* account = currentUser->getAccount();
    return account->getBalance();
}

Bank::TransactionState Bank::getCurrentTransactionState() const {
    return currentTransactionState;
}

void Bank::setCurrentTransactionState(TransactionState currentTransactionState) {
    this->currentTransactionState = currentTransactionState;
}


void Bank::login(std::string& userId, std::string& attemptedPassword) {

    User* tempUser = getUserById(userId);
    Authenticator::AuthenticationState authenticationState = Authenticator::UNAUTHENTICATED;
    if (tempUser) {

        User::UserDetails originalUserDetails = tempUser->getUserDetails();

        User::UserDetails attepmtedUserDetails{userId, attemptedPassword, "", ""};

        authenticationState = authenticator->authenticate(originalUserDetails, attepmtedUserDetails);
    } else {
        authenticationErrorState = Authenticator::WRONG_USER_NAME;
        return;
    }

    if (authenticationState == Authenticator::AUTHENTICATED) {
        setCurrentUser(tempUser);
        userType = tempUser->getUserType();
    }
    authenticationErrorState = authenticator->getAuthenticationErrorState();

}

void Bank::logout() {
    authenticator->unAuthenticate();
    authenticationErrorState = Authenticator::NO_ERROR;
    setCurrentUser(nullptr);
    userType = User::DEFAULT_STATE;
}

Authenticator::AuthenticationErrorState Bank::getAuthenticationErrorState() {
    return authenticationErrorState;
}

void Bank::setCustomerBalance(double amount) {
    Account* account = currentUser->getAccount();
    account->setBalance(amount);
}

User* Bank::getCurrentUser() {
    return currentUser;
}

void Bank::deposit(double amount) {

    if (amount > MAX_AMOUNT) {
        setCurrentTransactionState(FAILURE);
        return;
    }
    double currentBalance = getCustomerBalance();
    double newBalance = currentBalance + amount;
    setCustomerBalance(newBalance);
    setCurrentTransactionState(SUCCESS);
    recordTransaction(amount, Transaction::DEPOSIT_TRANSACTION, newBalance);
}

void Bank::withdraw(double amount) {

    double currentBalance = getCustomerBalance();
    if (amount > currentBalance) {
        setCurrentTransactionState(FAILURE);
        return;
    }
    double newBalance = currentBalance - amount;
    setCustomerBalance(newBalance);
    setCurrentTransactionState(SUCCESS);
    recordTransaction(amount, Transaction::WITHDRAW_TRANSACTION, newBalance);
}

std::string Bank::getLoginMessage() const {
    return authenticator->getLoginMessage();
}

void Bank::transfer(long receiverAccountNumber, double amount) {

    double senderCurrentBalance = getCustomerBalance();

    if (amount > MAX_AMOUNT || amount > senderCurrentBalance) {
        setCurrentTransactionState(FAILURE);
        return;
    }

    Account* receiverAccount = getAccountByNumber(receiverAccountNumber);

    if (receiverAccount) {

        double receiverCurrentBalance = receiverAccount->getBalance();
        double receiverNewBalance = receiverCurrentBalance + amount;
        receiverAccount->setBalance(receiverNewBalance);

        Account* senderAccount = getCustomerAccount();
        long senderAccountNumber = senderAccount->getAccountNumber();

        double senderNewBalance = senderCurrentBalance - amount;
        setCustomerBalance(senderNewBalance);

        setCurrentTransactionState(SUCCESS);
        
        recordTransaction(senderAccountNumber, receiverAccount, amount, Transaction::RECD_TRANSFER_TRANSACTION, receiverNewBalance);
        recordTransaction(receiverAccountNumber, getCustomerAccount(), amount, Transaction::SENT_TRANSFER_TRANSACTION, senderNewBalance);
    
    } else {
        std::cout << PRINT_DEST_ACC_DOES_NOT_EXIST << std::endl; 
        setCurrentTransactionState(FAILURE);
    }
}

std::string Bank::helperGetAccountStatement(int limit) const {
    Transaction** transactions = getCustomerAccount()->getAllTransactions();
    std::string combinedTransactions;
    for (int transactionIndex = limit - 1; transactionIndex >= 0; transactionIndex--) {
        combinedTransactions += (*(transactions + transactionIndex))->toString();
    }
    return combinedTransactions;
}

std::string Bank::getAccountFullStatement() const {
    return helperGetAccountStatement(getCustomerAccount()->getTransactionCount());
}

std::string Bank::getAccountMiniStatement() const {
    int transactionCount = getCustomerAccount()->getTransactionCount();
    int limit = (transactionCount > 10) ? 10 : transactionCount;
    return helperGetAccountStatement(limit);
}

void Bank::recordTransaction(double amount, Transaction::TransactionType transactionType, double newBalance) {
    Transaction* newTransaction = new Transaction(amount, transactionType, newBalance);
    getCustomerAccount()->addTransaction(newTransaction);
}

void Bank::recordTransaction(long otherAccNo, Account* destinationAccount, double amount, Transaction::TransactionType transactionType, double newBalance) {
    Transaction* newTransaction = new Transaction(otherAccNo, amount, transactionType, newBalance);

    destinationAccount->addTransaction(newTransaction);
}

Account* Bank::getCustomerAccount() const {
    Account* account = currentUser->getAccount();
    return account;
}

Bank::~Bank() {
    for (int userIndex = 0; userIndex < userCount; userIndex++) {
        delete *(allUsers + userIndex);
    }
    free(allUsers);
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

void Bank::setAuthenticationErrorState(Authenticator::AuthenticationErrorState authenticationErrorState) {
    this->authenticationErrorState = authenticationErrorState;
}

User* Bank::getUserById(const std::string& userID) const {
    for (int userIndex = 0; userIndex < userCount; userIndex++) {
        if ((*(allUsers + userIndex))->getUserID() == userID) {
            return *(allUsers + userIndex);
        }
    }
    return nullptr;
}

User* Bank::createUser(User::UserDetails& userDetails, Account::AccountType accountType) {
    User* newUser = nullptr;
    if (accountType == Account::ADMIN_ACCOUNT) {
        newUser = new Admin(userDetails);
    } else {
        newUser = new Customer(userDetails);
        Account* newAccount;
        if (accountType == Account::SAVINGS_ACCOUNT) {
            newAccount = new SavingsAccount();
        } else {
            newAccount = new CurrentAccount();
        }
        newUser->createAccount(newAccount);
    }
    return newUser;
}

void Bank::addUser(User* newUser) {
    userCount++;
    allUsers = (User**) realloc(allUsers, userCount * sizeof(User*));
    *(allUsers + (userCount - 1)) = newUser;
}

void Bank::deleteUser(User::UserDetails& userDetails) {

    if (currentUser->getUserID() == userDetails.userId) {
        std::cout << PRINT_CANNOT_DELETE_CURRENT_USER << std::endl;
        return;
    }

    int deleteUserIndex = getUserIndex(userDetails.userId);
    if (deleteUserIndex == -1) {
        std::cout << PRINT_USER_DOES_NOT_EXIST << std::endl;
        return;
    }

    delete *(allUsers + deleteUserIndex);
    for (int userIndex = deleteUserIndex; userIndex < userCount - 1; userIndex++) {
        *(allUsers + userIndex) = *(allUsers + userIndex + 1);
    }

    userCount--;
    if (userCount > 0) {
        allUsers = (User**) realloc(allUsers, userCount * sizeof(User*));
    } else {
        free(allUsers);
        allUsers = nullptr;
    }
}

int Bank::getUserIndex(std::string& userID) {
    for (int userIndex = 0; userIndex < userCount; userIndex++) {
        if ((*(allUsers + userIndex))->getUserID() == userID) {
            return userIndex;
        }
    }
    return -1;
}

std::string Bank::getAllCustomerDetails() const {
    std::string combinedCustomerDetails;
    for (int userIndex = 0; userIndex < userCount; userIndex++) {
        if ((*(allUsers + userIndex))->getUserType() == User::CUSTOMER) {
            combinedCustomerDetails += (*(allUsers + userIndex))->toString();
        }
    }
    if (combinedCustomerDetails.empty()) { 
        combinedCustomerDetails = PRINT_NO_CUSTOMER;
    }
    return combinedCustomerDetails;
}

Account* Bank::getAccountByNumber(long accountNumber) {
    Account* bankAccount = nullptr;
    for (int index = 0; index < userCount; index++) {
        User* tempUser = (*(allUsers + index));
        if (tempUser->getUserType() == User::CUSTOMER) {
            Account* tempAccount = tempUser->getAccount();
            if (tempAccount->getAccountNumber() == accountNumber) {
                bankAccount = tempAccount;
            }
        }
    }
    return bankAccount;
}

void Bank::reset() {

    for (int i = 0; i < userCount; i++) {
        delete *(allUsers + i);
    }
    free(allUsers);

    userCount = 0;
    allUsers = (User**) malloc(sizeof(User*));
    User::UserDetails defaultAdminDetails{PRINT_DEFAULT_ADMIN_ID, PRINT_DEFAULT_ADMIN_PASSWORD, PRINT_DEFAULT_ADMIN_NAME, PRINT_DEFAULT_ADMIN_LAST_NAME};
    User* defaultAdmin = createUser(defaultAdminDetails, Account::ADMIN_ACCOUNT);
    addUser(defaultAdmin);
    // setCurrentUser(getUserById(std::string(PRINT_DEFAULT_ADMIN_ID)));
    setCurrentUser(nullptr);
    setCurrentTransactionState(DEFAULT_STATE);
    authenticationErrorState = Authenticator::NO_ERROR;
}