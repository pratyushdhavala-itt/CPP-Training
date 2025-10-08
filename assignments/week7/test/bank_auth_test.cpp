#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "bank.h"
#include "mock_authenticator.h"
#include "customer.h"
#include "constants.h"

class BankAuthTest : public ::testing::Test {
protected:

    MockAuthenticator mockAuth;
    Bank* bank;
    User* newUser;

    void SetUp() override {

        bank = &Bank::getBankInstance(&mockAuth);

        User::UserDetails newUserDetails{"pratyushd", "correct_password", "Pratyush", "Dhavala"};
        newUser = bank->createUser(newUserDetails, Account::SAVINGS_ACCOUNT);
        bank->addUser(newUser);
    }

    void TearDown() override {

        bank->reset();
    }
};

TEST_F(BankAuthTest, GivenValidUserCredentials_WhenLoginCalled_ThenCurrentUserIsSetAndNoError) {

    EXPECT_CALL(mockAuth, authenticate(testing::_, testing::_))
        .WillOnce(testing::Return(Authenticator::AUTHENTICATED));

    EXPECT_CALL(mockAuth, getAuthenticationErrorState())
        .WillOnce(testing::Return(Authenticator::NO_ERROR));

    std::string attemptedId = "pratyushd", attemptedPassword = "1234";
    bank->login(attemptedId, attemptedPassword);

    EXPECT_EQ(newUser, bank->getCurrentUser());
    EXPECT_EQ(bank->getAuthenticationErrorState(), Authenticator::NO_ERROR);
    EXPECT_STREQ(bank->getErrorMessage().c_str(), "");
}

TEST_F(BankAuthTest, GivenValidUserWithWrongPassword_WhenLoginCalled_ThenAuthenticationFailsAndErrorIsWrongPassword) {

    EXPECT_CALL(mockAuth, authenticate(testing::_, testing::_))
        .WillOnce(testing::Return(Authenticator::UNAUTHENTICATED));

    EXPECT_CALL(mockAuth, getAuthenticationErrorState())
        .WillOnce(testing::Return(Authenticator::WRONG_PASSWORD));

    std::string attemptedId = "pratyushd", attemptedPassword = "wrong_password";
    bank->login(attemptedId, attemptedPassword);
    
    EXPECT_EQ(bank->getCurrentUser(), nullptr);
    EXPECT_EQ(bank->getAuthenticationErrorState(), Authenticator::WRONG_PASSWORD);
    EXPECT_STREQ(bank->getErrorMessage().c_str(), PRINT_WRONG_PASSWORD);
}

TEST_F(BankAuthTest, GivenNonExistentUser_WhenLoginCalled_ThenAuthenticationFailsAndErrorIsWrongUserName) {

    std::string attemptedId = "praneyd", attemptedPassword = "my_password";

    bank->login(attemptedId, attemptedPassword);

    EXPECT_EQ(bank->getCurrentUser(), nullptr);
    EXPECT_EQ(bank->getAuthenticationErrorState(), Authenticator::WRONG_USER_NAME);
    EXPECT_STREQ(bank->getErrorMessage().c_str(), PRINT_WRONG_USER_NAME);
}

TEST_F(BankAuthTest, GivenAuthenticatedUser_WhenLogoutCalled_ThenAuthenticationResetsAndCurrentUserIsCleared) {

    EXPECT_CALL(mockAuth, authenticate(testing::_, testing::_))
        .WillOnce(testing::Return(Authenticator::AUTHENTICATED));

    EXPECT_CALL(mockAuth, getAuthenticationErrorState())
        .WillOnce(testing::Return(Authenticator::NO_ERROR));

    std::string attemptedId = "pratyushd", attemptedPassword = "correct_password";
    bank->login(attemptedId, attemptedPassword);
    ASSERT_EQ(bank->getCurrentUser(), newUser);

    EXPECT_CALL(mockAuth, unAuthenticate()).Times(1);
    bank->logout();

    EXPECT_EQ(bank->getCurrentUser(), nullptr);
    EXPECT_EQ(bank->getAuthenticationErrorState(), Authenticator::NO_ERROR);
}

TEST_F(BankAuthTest, GivenAuthenticatedUser_WhenGetLoginMessageCalled_ThenCorrectWelcomeMessageIsReturned) {

    EXPECT_CALL(mockAuth, authenticate(testing::_, testing::_))
        .WillOnce(testing::Return(Authenticator::AUTHENTICATED));
    EXPECT_CALL(mockAuth, getAuthenticationErrorState())
        .WillOnce(testing::Return(Authenticator::NO_ERROR));

    EXPECT_CALL(mockAuth, getLoginMessage())
        .WillOnce(testing::Return("Welcome Pratyush Dhavala"));

    std::string attemptedId = "pratyushd", attemptedPassword = "correct_password";
    bank->login(attemptedId, attemptedPassword);

    EXPECT_STREQ(bank->getLoginMessage().c_str(), "Welcome Pratyush Dhavala");
}
