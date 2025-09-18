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

public:

    User();
    User(std::string userFirstName, std::string userLastName, std::string userID, std::string userPassword, UserType userType);

    std::string getUserID() const;
    std::string getPassword() const;
    UserType getUserType() const;
    std::string getUserFullName() const;

    virtual void showMenu() const = 0;

    virtual ~User();
};

#endif