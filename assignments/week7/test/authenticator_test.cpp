#include <gtest/gtest.h>
#include "authenticator.h"
#include "constants.h"

TEST(AuthenticatorTest,
     GivenAuthenticator_WhenConstructed_ThenStateIsUnauthenticatedAndErrorIsNoError) {
    
    Authenticator auth;

    EXPECT_EQ(auth.getAuthenticationState(), Authenticator::UNAUTHENTICATED);
    EXPECT_EQ(auth.getAuthenticationErrorState(), Authenticator::NO_ERROR);
}

TEST(AuthenticatorTest,
     GivenMatchingUserDetails_WhenAuthenticateCalled_ThenStateIsAuthenticatedAndErrorIsNoError) {
    
    User::UserDetails stored{"pratyushd", "my_password", "Pratyush", "Dhavala"};
    User::UserDetails attempt{"pratyushd", "my_password", "Pratyush", "Dhavala"};

    Authenticator auth;
    Authenticator::AuthenticationState authenticationState = auth.authenticate(stored, attempt);

    EXPECT_EQ(authenticationState, Authenticator::AUTHENTICATED);
    EXPECT_EQ(auth.getAuthenticationState(), Authenticator::AUTHENTICATED);
    EXPECT_EQ(auth.getAuthenticationErrorState(), Authenticator::NO_ERROR);
}

TEST(AuthenticatorTest,
     GivenWrongPassword_WhenAuthenticateCalled_ThenStateIsUnauthenticatedAndErrorIsWrongPassword) {
    
    User::UserDetails stored{"pratyushd", "my_password", "Pratyush", "Dhavala"};
    User::UserDetails attempt{"pratyushd", "wrong_password", "Pratyush", "Dhavala"};

    Authenticator auth;
    Authenticator::AuthenticationState authenticationState = auth.authenticate(stored, attempt);

    EXPECT_EQ(authenticationState, Authenticator::UNAUTHENTICATED);
    EXPECT_EQ(auth.getAuthenticationState(), Authenticator::UNAUTHENTICATED);
    EXPECT_EQ(auth.getAuthenticationErrorState(), Authenticator::WRONG_PASSWORD);
}

TEST(AuthenticatorTest,
     GivenAuthenticatedUser_WhenGetLoginMessageCalled_ThenCorrectWelcomeMessageIsReturned) {
    
    Authenticator auth;
    User::UserDetails stored{"pratyushd", "my_password", "Pratyush", "Dhavala"};
    auth.setCurrentUserDetails(stored);

    std::string loginMessage = auth.getLoginMessage();
    std::string expectedLoginMessage = PRINT_LOGIN + stored.userId + PRINT_LOGIN_WELCOME + stored.userFirstName + " " + stored.userLastName + PRINT_NEXT_LINE;


    EXPECT_STREQ(loginMessage.c_str(), expectedLoginMessage.c_str());
}

TEST(AuthenticatorTest,
     GivenAuthenticatedUser_WhenUnAuthenticateCalled_ThenStateResetsToUnauthenticated) {

    Authenticator auth;
    User::UserDetails stored{"pratyushd", "my_password", "Pratyush", "Dhavala"};
    auth.setCurrentUserDetails(stored);

    auth.unAuthenticate();

    EXPECT_EQ(auth.getAuthenticationState(), Authenticator::UNAUTHENTICATED);
    EXPECT_EQ(auth.getCurrentUserDetails(), User::UserDetails{});
}
