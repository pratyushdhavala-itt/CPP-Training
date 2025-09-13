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

private:

    User* authenticatedUser;
    int userCount;

public:
    Authenticator();

    void authenticate(User* user, std::string& password);
    User* getAuthenticatedUser();
    void unAuthenticate();
};

#endif