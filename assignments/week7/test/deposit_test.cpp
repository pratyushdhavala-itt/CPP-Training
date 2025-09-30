#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "bank.h"
#include "authenticator.h"
#include "mock_account.h"
#include "customer.h"

struct DepositTestCase {
    double depositAmount;
    double initialBalance;
    double expectedBalance;
    Bank::TransactionState expectedState;
};

class BankDepositUnitTest : public ::testing::TestWithParam<DepositTestCase> {
protected:
    Bank* bank;
    Authenticator auth;
    MockAccount* mockAccount;
    Customer* customer;

    void SetUp() override {
        bank = &Bank::getBankInstance(&auth);

        User::UserDetails details{"pratyushd", "1234", "Pratyush", "Dhavala"};
        customer = new Customer(details);

        mockAccount = new MockAccount();
        customer->createAccount(mockAccount);

        bank->setCurrentUser(customer);
    }

    void TearDown() override {

        customer->createAccount(nullptr);
        delete customer;
        delete mockAccount;

        bank->reset();
    }
};

TEST_P(BankDepositUnitTest, GivenInitialBalance_WhenDepositPerformed_ThenBalanceAndStateAreCorrect) {
    DepositTestCase testCase = GetParam();

    if (testCase.expectedState == Bank::SUCCESS) {

        EXPECT_CALL(*mockAccount, getBalance())
            .WillOnce(testing::Return(testCase.initialBalance));

        EXPECT_CALL(*mockAccount, setBalance(testCase.expectedBalance))
            .Times(1);

        EXPECT_CALL(*mockAccount, addTransaction(testing::_))
            .Times(1);

    } else if (testCase.expectedState == Bank::FAILURE) {

        EXPECT_CALL(*mockAccount, getBalance())
            .Times(0);

        EXPECT_CALL(*mockAccount, setBalance(testing::_)).Times(0);
    }

    bank->deposit(testCase.depositAmount);

    EXPECT_EQ(bank->getCurrentTransactionState(), testCase.expectedState);
}

INSTANTIATE_TEST_SUITE_P(
    DepositScenarios,
    BankDepositUnitTest,
    ::testing::Values(
        DepositTestCase{500, 10000, 10500, Bank::SUCCESS},                
        DepositTestCase{Bank::MAX_AMOUNT, 10000, 10000 + Bank::MAX_AMOUNT, Bank::SUCCESS}, 
        DepositTestCase{Bank::MAX_AMOUNT + 1, 10000, 10000, Bank::FAILURE},
        DepositTestCase{0, 10000, 10000, Bank::SUCCESS}                            
    )
);
