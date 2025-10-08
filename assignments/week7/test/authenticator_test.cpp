#include <gtest/gtest.h>
#include "authenticator.h"
#include "constants.h"

class AuthenticatorTest : public testing::Test {

protected:
    Authenticator auth;
    User::UserDetails stored;

    void SetUp() override {
        stored = {"pratyushd", "my_password", "Pratyush", "Dhavala"};
    }
};

TEST_F(AuthenticatorTest, GivenAuthenticator_WhenConstructed_ThenStateIsUnauthenticatedAndErrorIsNoError) {

    EXPECT_EQ(auth.getAuthenticationState(), Authenticator::UNAUTHENTICATED);
    EXPECT_EQ(auth.getAuthenticationErrorState(), Authenticator::NO_ERROR);
}

TEST_F(AuthenticatorTest, GivenCorrectUserDetails_WhenAuthenticateCalled_ThenStateIsAuthenticatedAndErrorIsNoError) {
    
    User::UserDetails attempt{"pratyushd", "my_password", "Pratyush", "Dhavala"};

    Authenticator::AuthenticationState authenticationState = auth.authenticate(stored, attempt);

    EXPECT_EQ(authenticationState, Authenticator::AUTHENTICATED);
    EXPECT_EQ(auth.getAuthenticationState(), Authenticator::AUTHENTICATED);
    EXPECT_EQ(auth.getAuthenticationErrorState(), Authenticator::NO_ERROR);
}

TEST_F(AuthenticatorTest, GivenWrongPassword_WhenAuthenticateCalled_ThenStateIsUnauthenticatedAndErrorIsWrongPassword) {
    
    User::UserDetails attempt{"pratyushd", "wrong_password", "Pratyush", "Dhavala"};

    Authenticator::AuthenticationState authenticationState = auth.authenticate(stored, attempt);

    EXPECT_EQ(authenticationState, Authenticator::UNAUTHENTICATED);
    EXPECT_EQ(auth.getAuthenticationState(), Authenticator::UNAUTHENTICATED);
    EXPECT_EQ(auth.getAuthenticationErrorState(), Authenticator::WRONG_PASSWORD);
}

TEST_F(AuthenticatorTest, GivenAuthenticatedUser_WhenGetLoginMessageCalled_ThenCorrectWelcomeMessageIsReturned) {
    
    auth.setCurrentUserDetails(stored);

    std::string loginMessage = auth.getLoginMessage();
    std::string expectedLoginMessage = PRINT_LOGIN + stored.userId + PRINT_LOGIN_WELCOME + stored.userFirstName + " " + stored.userLastName + PRINT_NEXT_LINE;

    EXPECT_STREQ(loginMessage.c_str(), expectedLoginMessage.c_str());
}

TEST_F(AuthenticatorTest, GivenAuthenticatedUser_WhenUnAuthenticateCalled_ThenStateResetsToUnauthenticated) {

    auth.setCurrentUserDetails(stored);

    auth.unAuthenticate();

    EXPECT_EQ(auth.getAuthenticationState(), Authenticator::UNAUTHENTICATED);
    EXPECT_EQ(auth.getCurrentUserDetails(), User::UserDetails{});
}
