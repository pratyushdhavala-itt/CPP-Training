#include <iostream>

#include "user.h"

User::User(std::string userFirstName, std::string userLastName, std::string userID, std::string userPassword, UserType userType, Account::AccountType accountType) 
    : userID{userID},
    userType{userType},
    accountType{accountType},
    userPassword{userPassword},
    userLastName{userLastName},
    userFirstName{userFirstName} {

}

User::User() {

}

bool User::checkUserPassword(std::string attemptedPassword) {
    bool passwordMatch = false;
    if (attemptedPassword == userPassword) {
        passwordMatch = true;
    }
    return passwordMatch;
}

std::string User::getUserID() {
    return userID;
}

User::UserType User::getUserType() {
    return userType;
}

std::string User::getUserFullName() {
    return userFirstName + " " + userLastName;
}

User::~User() {}