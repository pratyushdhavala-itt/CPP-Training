#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "bank.h"
#include "authenticator.h"
#include "mock_account.h"
#include "customer.h"

struct TransferTestCase {
    double transferAmount;
    double senderInitialBalance;
    double receiverInitialBalance;
    double expectedSenderBalance;
    double expectedReceiverBalance;
    Bank::TransactionState expectedState;
    bool receiverExists;
};

class BankTransferUnitTest : public ::testing::TestWithParam<TransferTestCase> {
protected:
    Bank* bank;
    Authenticator auth;
    MockAccount* senderMockAccount;
    MockAccount* receiverMockAccount;
    Customer* senderCustomer;
    Customer* receiverCustomer;

    void SetUp() override {
        bank = &Bank::getBankInstance(&auth);

        User::UserDetails senderDetails{"pratyushd", "1234", "Pratyush", "Dhavala"};
        senderCustomer = new Customer(senderDetails);
        senderMockAccount = new MockAccount();
        ON_CALL(*senderMockAccount, getAccountNumber()).WillByDefault(testing::Return(1001));

        senderCustomer->createAccount(senderMockAccount);
        bank->addUser(senderCustomer);

        bank->setCurrentUser(senderCustomer);

        if (GetParam().receiverExists) {

            User::UserDetails receiverDetails{"praneyd", "1234", "Praney", "Dhavala"};
            receiverCustomer = new Customer(receiverDetails);
            receiverMockAccount = new MockAccount();
            ON_CALL(*receiverMockAccount, getAccountNumber()).WillByDefault(testing::Return(1002));

            receiverCustomer->createAccount(receiverMockAccount);
            bank->addUser(receiverCustomer);
        } else {
            receiverCustomer = nullptr;
            receiverMockAccount = nullptr;
        }
    }

    void TearDown() override {

        senderCustomer->createAccount(nullptr);
        delete senderMockAccount;

        if (receiverCustomer) {
            receiverCustomer->createAccount(nullptr);
            delete receiverMockAccount;
        }
        
        bank->reset();   
    }
};

TEST_P(BankTransferUnitTest,
       GivenSenderAndReceiver_WhenTransferPerformed_ThenBalancesAndStateAreCorrect) {
    
    TransferTestCase testCase = GetParam();

    EXPECT_CALL(*senderMockAccount, getBalance())
        .WillOnce(testing::Return(testCase.senderInitialBalance));

    if (testCase.expectedState == Bank::SUCCESS && testCase.receiverExists) {
        EXPECT_CALL(*receiverMockAccount, getBalance())
            .WillOnce(testing::Return(testCase.receiverInitialBalance));
        EXPECT_CALL(*receiverMockAccount, setBalance(testCase.expectedReceiverBalance))
            .Times(1);
        EXPECT_CALL(*senderMockAccount, setBalance(testCase.expectedSenderBalance))
            .Times(1);
    } else {
        // EXPECT_CALL(*receiverMockAccount, getBalance()).Times(0);
        // EXPECT_CALL(*receiverMockAccount, setBalance(testing::_)).Times(0);
        EXPECT_CALL(*senderMockAccount, setBalance(testing::_)).Times(0);
    }

    bank->transfer(1002, testCase.transferAmount);

    EXPECT_EQ(bank->getCurrentTransactionState(), testCase.expectedState);
}

INSTANTIATE_TEST_SUITE_P(
    TransferScenarios,
    BankTransferUnitTest,
    ::testing::Values(
        TransferTestCase{500, 10000, 8000, 9500, 8500, Bank::SUCCESS, true},           // normal transfer
        TransferTestCase{10000, 10000, 2000, 0, 12000, Bank::SUCCESS, true},           // transfer full balance
        TransferTestCase{15000, 10000, 5000, 10000, 5000, Bank::FAILURE, true},        // insufficient funds
        TransferTestCase{Bank::MAX_AMOUNT + 1, 20000, 5000, 20000, 5000, Bank::FAILURE, true}, // exceeds max
        TransferTestCase{500, 10000, 5000, 10000, 5000, Bank::FAILURE, false}          // receiver doesn't exist
    )
);
