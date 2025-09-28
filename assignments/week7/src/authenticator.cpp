#include "authenticator.h"
#include "bank.h"
#include "constants.h"

Authenticator::Authenticator() : authenticationState{UNAUTHENTICATED}, authenticationErrorState{NO_ERROR} {}

Authenticator::AuthenticationState Authenticator::authenticate(const User::UserDetails& originalUserDetails, const User::UserDetails& attemptedUserDetails) {

    if (originalUserDetails.userPassword != attemptedUserDetails.userPassword) {
        authenticationErrorState = WRONG_PASSWORD;
    } else {
        setCurrentUserDetails(originalUserDetails);
        authenticationState = AUTHENTICATED;
    }
    return authenticationState;
}

void Authenticator::setCurrentUserDetails(User::UserDetails userDetails) {
    this->currentUserDetails = userDetails;
}

User::UserDetails Authenticator::getCurrentUserDetails() {
    return currentUserDetails;
}

std::string Authenticator::getLoginMessage() const {
    return PRINT_LOGIN + currentUserDetails.userId + PRINT_LOGIN_WELCOME + currentUserDetails.userFirstName + " " + currentUserDetails.userLastName + PRINT_NEXT_LINE;
}

Authenticator::AuthenticationState Authenticator::getAuthenticationState() {
    return authenticationState;
}
Authenticator::AuthenticationErrorState Authenticator::getAuthenticationErrorState() {
    return authenticationErrorState;
}

void Authenticator::unAuthenticate() {
    authenticationState = UNAUTHENTICATED;
    setCurrentUserDetails({});
}
