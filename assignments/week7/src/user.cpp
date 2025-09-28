#include <iostream>

#include "user.h"

User::User(UserDetails userDetails, UserType userType) 
    : 
    userDetails{userDetails},
    userType{userType} {}

User::UserDetails User::getUserDetails() const {
    return userDetails;
}

std::string User::getPassword() const {
    return userDetails.userPassword;
}

std::string User::getUserID() const {
    return userDetails.userId;
}

User::UserType User::getUserType() const {
    return userType;
}

std::string User::getUserFullName() const {
    return userDetails.userFirstName + " " + userDetails.userLastName;
}

std::string User::toString() {
    return "";
}

Account* User::getAccount() {
    return nullptr;
}

void User::createAccount(Account* account) {}

bool User::UserDetails::operator==(const UserDetails& otherUserDetails) const {
    return userId == otherUserDetails.userId && userPassword == otherUserDetails.userPassword;
}

User::~User() {}