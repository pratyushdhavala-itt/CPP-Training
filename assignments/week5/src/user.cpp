#include <iostream>

#include "user.h"

User::User(std::string userFirstName, std::string userLastName, std::string userID, std::string userPassword, UserType userType) 
    : userID{userID},
    userType{userType},
    userPassword{userPassword},
    userLastName{userLastName},
    userFirstName{userFirstName} {

}

User::User() {

}

std::string User::getPassword() const {
    return userPassword;
}

std::string User::getUserID() const {
    return userID;
}

User::UserType User::getUserType() const {
    return userType;
}

std::string User::getUserFullName() const {
    return userFirstName + " " + userLastName;
}

User::~User() {}