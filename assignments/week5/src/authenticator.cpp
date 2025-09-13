#include "authenticator.h"
#include "bank.h"

Authenticator::Authenticator() : authenticatedUser{nullptr} {}

void Authenticator::authenticate(User* user, std::string& attemptedPassword) {

    if (user->checkUserPassword(attemptedPassword)) {
        authenticatedUser = user;
    }
}

User* Authenticator::getAuthenticatedUser() {
    return authenticatedUser;
}

void Authenticator::unAuthenticate() {
    authenticatedUser = nullptr;
}
