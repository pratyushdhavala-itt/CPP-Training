#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "bank.h"
#include "authenticator.h"
#include "mock_account.h"
#include "customer.h"


struct WithdrawTestCase {
    double withdrawAmount;                
    double initialBalance;                
    double expectedBalance;               
    Bank::TransactionState expectedState; 
};

class BankWithdrawUnitTest : public ::testing::TestWithParam<WithdrawTestCase> {
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

TEST_P(BankWithdrawUnitTest, GivenInitialBalance_WhenWithdrawPerformed_ThenBalanceAndStateAreCorrect) {
    WithdrawTestCase testCase = GetParam();

    EXPECT_CALL(*mockAccount, getBalance())
        .WillOnce(testing::Return(testCase.initialBalance));

    if (testCase.expectedState == Bank::SUCCESS) {
        EXPECT_CALL(*mockAccount, setBalance(testCase.expectedBalance))
            .Times(1);
    } else {
        EXPECT_CALL(*mockAccount, setBalance(testing::_)).Times(0);
    }

    bank->withdraw(testCase.withdrawAmount);

    EXPECT_EQ(bank->getCurrentTransactionState(), testCase.expectedState);
}

INSTANTIATE_TEST_SUITE_P(
    WithdrawScenarios,
    BankWithdrawUnitTest,
    ::testing::Values(
        WithdrawTestCase{500, 10000, 9500, Bank::SUCCESS},      // normal withdraw
        WithdrawTestCase{10000, 10000, 0, Bank::SUCCESS},       // withdraw full balance
        WithdrawTestCase{15000, 10000, 10000, Bank::FAILURE},   // withdraw more than balance
        WithdrawTestCase{0, 10000, 10000, Bank::SUCCESS}      // withdraw zero
        //WithdrawTestCase{-500, 10000, 10500, Bank::SUCCESS}     // withdraw negative (bug: acts like deposit)
    )
);
