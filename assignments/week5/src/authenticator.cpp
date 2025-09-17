#include "authenticator.h"
#include "bank.h"
#include "constants.h"

Authenticator::Authenticator() : authenticatedUser{nullptr}, allUsers{(User**) malloc(sizeof(User*))}, userCount{1}, authenticationState{UNAUTHENTICATED} {
    Admin* admin = new Admin();
    *(allUsers) = admin;
}

Authenticator::AuthenticationState Authenticator::authenticate(std::string& userID, std::string& attemptedPassword) {

    User* tempUser = findUserById(userID);
    if (tempUser) {
        if (tempUser->getPassword() == attemptedPassword) {
            authenticationState = AUTHENTICATED;
            authenticationErrorState = NO_ERROR;
            authenticatedUser = tempUser;
        } else {
            authenticationErrorState = WRONG_PASSWORD;
        }
    } else {
        authenticationErrorState = WRONG_USER_NAME;
    }
    return authenticationState;
}

User* Authenticator::getAuthenticatedUser() const {
    return authenticatedUser;
}

std::string Authenticator::getLoginMessage() const {
    return PRINT_LOGIN + authenticatedUser->getUserID() + PRINT_LOGIN_WELCOME + authenticatedUser->getUserFullName() + PRINT_NEXT_LINE;
}

Authenticator::AuthenticationState Authenticator::getAuthenticationState() {
    return authenticationState;
}
Authenticator::AuthenticationErrorState Authenticator::getAuthenticationErrorState() {
    return authenticationErrorState;
}

void Authenticator::unAuthenticate() {
    authenticatedUser = nullptr;
}

User* Authenticator::findUserById(std::string& userID) const {
    for (int userIndex = 0; userIndex < userCount; userIndex++) {
        if ((*(allUsers + userIndex))->getUserID() == userID) {
            return *(allUsers + userIndex);
        }
    }
    return nullptr;
}

void Authenticator::addUser(std::string& userFirstName, std::string& userLastName, std::string& userID, std::string& userPassword, Account::AccountType accountType) {
    userCount++;
    allUsers = (User**) realloc(allUsers, userCount * sizeof(User*));
    if (accountType != Account::ADMIN_ACCOUNT) {
        *(allUsers + (userCount - 1)) = new Customer(userFirstName, userLastName, userID, userPassword, accountType);
    } else {
        *(allUsers + (userCount - 1)) = new Admin(userFirstName, userLastName, userID, userPassword);
    }
    
}

void Authenticator::deleteUser(std::string& userID) {

    if (authenticatedUser->getUserID() == userID) {
        std::cout << PRINT_CANNOT_DELETE_CURRENT_USER << std::endl;
        return;
    }

    int deleteUserIndex = getUserIndex(userID);
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

int Authenticator::getUserIndex(std::string& userID) {
    for (int userIndex = 0; userIndex < userCount; userIndex++) {
        if ((*(allUsers + userIndex))->getUserID() == userID) {
            return userIndex;
        }
    }
    return -1;
}

std::string Authenticator::getAllCustomerDetails() const {
    std::string combinedCustomerDetails;
    for (int userIndex = 0; userIndex < userCount; userIndex++) {
        Customer* tempCustomer = dynamic_cast<Customer*>(*(allUsers + userIndex));
        if (tempCustomer) {
            combinedCustomerDetails += tempCustomer->toString();
        }
    }
    if (combinedCustomerDetails.empty()) { 
        combinedCustomerDetails = PRINT_NO_CUSTOMER;
    }
    return combinedCustomerDetails;
}

Account* Authenticator::findAccountByNumber(long accountNumber) {
    Account* bankAccount = nullptr;
    for (int index = 0; index < userCount; index++) {
        Customer* tempCustomer = dynamic_cast<Customer*>(*(allUsers + index));
        if (tempCustomer) {
            if (tempCustomer->getCustomerAccount()->getAccountNumber() == accountNumber) {
                bankAccount = tempCustomer->getCustomerAccount();
            }
        }
    }
    return bankAccount;
}

Authenticator::~Authenticator() {
    for (int userIndex = 0; userIndex < userCount; userIndex++) {
        delete *(allUsers + userIndex);
    }
    free(allUsers);
}