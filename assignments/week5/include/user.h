#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include "account.h"

class User {

public:
    enum UserType {
        ADMIN = 1,
        CUSTOMER = 2,
    };

protected:

    std::string userID;
    std::string userPassword; 
    std::string userFirstName;
    std::string userLastName;
    UserType userType;
    Account::AccountType accountType;

public:

    User();
    User(std::string userFirstName, std::string userLastName, std::string userID, std::string userPassword, UserType userType, Account::AccountType accountType);

    std::string getUserID();
    bool checkUserPassword(std::string password);
    UserType getUserType();
    std::string getUserFullName();

    virtual void showMenu() = 0;

    virtual ~User();
};

#endif