#include <gtest/gtest.h>
#include "bank.h"
#include "authenticator.h"
#include "customer.h"
#include "mock_account.h"
#include "constants.h"
class BankGetterSetterTest : public ::testing::Test {
protected:
    Bank* bank;
    Authenticator auth;
    MockAccount* mockAccount;
    User::UserDetails newUserDetails;

    void SetUp() override {
        bank = &Bank::getBankInstance(&auth);
        mockAccount = new MockAccount();
        newUserDetails = {"pratyushd", "1234", "Pratyush", "Dhavala"};
    }

    void TearDown() override {
        bank->reset(); 
        delete mockAccount;
    }
};

TEST_F(BankGetterSetterTest,
       GivenTransaction_WhenRecordTransactionCalled_ThenTransactionIsAddedToAccount) {

    User* customer = new Customer(newUserDetails);
    customer->createAccount(mockAccount);
    bank->setCurrentUser(customer);

    EXPECT_CALL(*mockAccount, addTransaction(testing::_));

    bank->recordTransaction(1000, Transaction::DEPOSIT_TRANSACTION, 2000);
}

TEST_F(BankGetterSetterTest, 
       GivenErrorState_WhenGetAuthenticationErrorStateCalled_ThenCorrectStateIsReturned) {

    bank->setAuthenticationErrorState(Authenticator::NO_ERROR);

    Authenticator::AuthenticationErrorState authenticationErrorState = bank->getAuthenticationErrorState();

    EXPECT_EQ(authenticationErrorState, Authenticator::NO_ERROR);
}

TEST_F(BankGetterSetterTest,
       GivenCustomer_WhenSetCurrentUserCalled_ThenUserTypeIsCustomer) {

    User* newUser = new Customer(newUserDetails);

    bank->setCurrentUser(newUser);

    EXPECT_EQ(bank->getUserType(), User::CUSTOMER);
}

TEST_F(BankGetterSetterTest,
       GivenAdmin_WhenSetCurrentUserCalled_ThenUserTypeIsAdmin) {

    User* newUser = new Admin(newUserDetails);

    bank->setCurrentUser(newUser);

    EXPECT_EQ(bank->getUserType(), User::ADMIN);
}

TEST_F(BankGetterSetterTest,
       GivenCustomerWithAccount_WhenSetCustomerBalanceCalled_ThenAccountSetBalanceCalled) {

    User* customer = new Customer(newUserDetails);
    customer->createAccount(mockAccount);
    bank->setCurrentUser(customer);
    double expectedAmount = 20000.0;
    EXPECT_CALL(*mockAccount, setBalance(expectedAmount))
        .Times(1);

    bank->setCustomerBalance(expectedAmount);
}

TEST_F(BankGetterSetterTest,
       GivenCustomerWithAccount_WhenGetCustomerBalanceCalled_ThenAccountGetBalanceCalledAndValueReturned) {

    User* customer = new Customer(newUserDetails);
    customer->createAccount(mockAccount);
    bank->setCurrentUser(customer);
    double expectedAmount = 20000.0;
    EXPECT_CALL(*mockAccount, getBalance())
        .WillOnce(testing::Return(expectedAmount));

    double actualAmount = bank->getCustomerBalance();

    EXPECT_EQ(actualAmount, expectedAmount);
}

TEST_F(BankGetterSetterTest,
       GivenTransactionState_WhenSetCurrentTransactionStateCalled_ThenGetCurrentTransactionStateReturnsSameValue) {

    EXPECT_EQ(bank->getCurrentTransactionState(), Bank::DEFAULT_STATE);

    bank->setCurrentTransactionState(Bank::SUCCESS);
    EXPECT_EQ(bank->getCurrentTransactionState(), Bank::SUCCESS);

    bank->setCurrentTransactionState(Bank::FAILURE);
    EXPECT_EQ(bank->getCurrentTransactionState(), Bank::FAILURE);
}

TEST_F(BankGetterSetterTest,
       GivenAuthenticationErrorState_WhenSetAuthenticationErrorStateCalled_ThenGetAuthenticationErrorStateReturnsSameValue) {

    EXPECT_EQ(bank->getAuthenticationErrorState(), Authenticator::NO_ERROR);
    
    bank->setAuthenticationErrorState(Authenticator::WRONG_PASSWORD);
    EXPECT_EQ(bank->getAuthenticationErrorState(), Authenticator::WRONG_PASSWORD);
    
    bank->setAuthenticationErrorState(Authenticator::WRONG_USER_NAME);
    EXPECT_EQ(bank->getAuthenticationErrorState(), Authenticator::WRONG_USER_NAME);
}

TEST_F(BankGetterSetterTest,
       GivenAuthenticationErrorState_WhenGetErrorMessageCalled_ThenCorrectMessageIsReturned) {

    bank->setAuthenticationErrorState(Authenticator::WRONG_PASSWORD);
    EXPECT_STREQ(bank->getErrorMessage().c_str(), PRINT_WRONG_PASSWORD);

    bank->setAuthenticationErrorState(Authenticator::WRONG_USER_NAME);
    EXPECT_STREQ(bank->getErrorMessage().c_str(), PRINT_WRONG_USER_NAME);

    bank->setAuthenticationErrorState(Authenticator::NO_ERROR);
    EXPECT_STREQ(bank->getErrorMessage().c_str(), "");
}

TEST_F(BankGetterSetterTest,
       GivenCustomer_WhenGetAccountStatementCalled_ThenReturnAccountStatement) {

    User* customer = new Customer(newUserDetails);
    customer->createAccount(mockAccount);
    bank->setCurrentUser(customer);
    Transaction* t1 = new Transaction(1000, Transaction::DEPOSIT_TRANSACTION, 1500);
    Transaction** t_list = &t1;

    EXPECT_CALL(*mockAccount, getTransactionCount())
        .Times(2)
        .WillRepeatedly(testing::Return(1));

    EXPECT_CALL(*mockAccount, getAllTransactions())
        .Times(2)
        .WillRepeatedly(testing::Return(t_list));

    EXPECT_EQ(t1->toString(), bank->getAccountFullStatement());
    EXPECT_EQ(t1->toString(), bank->getAccountMiniStatement());

    delete t1;
}