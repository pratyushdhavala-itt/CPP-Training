#ifndef USER_H
#define USER_H

#include <iostream>
#include "account.h"

class User {

public:
    enum UserType {
        DEFAULT_STATE = 0,
        ADMIN = 1,
        CUSTOMER = 2,
    };

    struct UserDetails {
        std::string userId;
        std::string userPassword; 
        std::string userFirstName;
        std::string userLastName;

        bool operator==(const UserDetails& otherUserDetails) const;
    };

protected:

    UserDetails userDetails;
    UserType userType;

public:

    User(UserDetails userDetails, UserType userType);

    virtual UserDetails getUserDetails() const;
    virtual std::string getUserID() const;
    virtual std::string getPassword() const;
    virtual UserType getUserType() const;
    virtual std::string getUserFullName() const;

    virtual void showMenu() const = 0;
    virtual std::string toString();
    virtual Account* getAccount();
    virtual void createAccount(Account* account);
    virtual ~User();
};

#endif