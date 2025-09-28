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

    User::UserDetails currentUserDetails;
    AuthenticationState authenticationState;
    AuthenticationErrorState authenticationErrorState;

public:
    Authenticator();

    virtual void setCurrentUserDetails(User::UserDetails userDetails);
    virtual User::UserDetails getCurrentUserDetails();
    virtual AuthenticationState getAuthenticationState();
    virtual AuthenticationErrorState getAuthenticationErrorState();
    virtual AuthenticationState authenticate(const User::UserDetails& userOne, const User::UserDetails& userTwo);
    virtual void unAuthenticate();
    virtual std::string getLoginMessage() const;

};

#endif