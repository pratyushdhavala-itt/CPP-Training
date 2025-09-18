#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include "user.h"

class Authenticator {

public:
    enum AuthenticationErrorState {
        NO_ERROR = 1,
        WRONG_USER_NAME = 2,
        WRONG_PASSWORD = 3,
    };

    enum AuthenticationState {
        AUTHENTICATED = 1,
        UNAUTHENTICATED = 2,
    };

private:

    User* authenticatedUser;
    int userCount;
    User** allUsers;
    AuthenticationState authenticationState;
    AuthenticationErrorState authenticationErrorState;

public:
    Authenticator();

    AuthenticationState getAuthenticationState();
    AuthenticationErrorState getAuthenticationErrorState();
    AuthenticationState authenticate(std::string& userID, std::string& password);
    void unAuthenticate();
    User* findUserById(std::string& userID) const;
    std::string getLoginMessage() const;
    User* getAuthenticatedUser() const;
    void addUser(std::string& userFirstName, std::string& userLastName, std::string& userID, std::string& userPassword, Account::AccountType accountType);
    void deleteUser(std::string& userID);
    int getUserIndex(std::string& userID);
    std::string getAllCustomerDetails() const;
    Account* findAccountByNumber(long accountNumber);
    

    ~Authenticator();
};

#endif