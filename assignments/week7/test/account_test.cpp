#include <gtest/gtest.h>
#include "account.h"
#include "savings_account.h"
#include "current_account.h"
#include "user.h"
#include "customer.h"

TEST(AccountTest,
     GivenNewSavingsAccount_WhenConstructed_ThenInitialBalanceAndUniqueAccountNumberAreSet) {
    
    Account* bankAccount = new SavingsAccount();

    EXPECT_EQ(bankAccount->getBalance(), Account::INITIAL_BALANCE);
    EXPECT_EQ(bankAccount->getAccountNumber(), Account::DEFAULT_ACC_NO + 1);
}

TEST(AccountTest,
     GivenAccount_WhenSetBalanceCalled_ThenGetBalanceReturnsUpdatedValue) {
    
    Account* bankAccount = new SavingsAccount();

    EXPECT_EQ(bankAccount->getBalance(), Account::INITIAL_BALANCE);

    bankAccount->setBalance(8700.0);

    EXPECT_EQ(bankAccount->getBalance(), 8700.0);

}

TEST(AccountTest,
     GivenSavingsAccount_WhenTransactionsAreAdded_ThenTheyAreStoredAndCountIsCorrect) {

    Account* bankAccount = new SavingsAccount();

    EXPECT_EQ(bankAccount->getTransactionCount(), 0);

    Transaction* transactionOne = new Transaction(1000, Transaction::DEPOSIT_TRANSACTION, 11000);
    Transaction* transactionTwo = new Transaction(500, Transaction::WITHDRAW_TRANSACTION, 10500);

    bankAccount->addTransaction(transactionOne);
    bankAccount->addTransaction(transactionTwo);

    EXPECT_EQ(bankAccount->getTransactionCount(), 2);

    Transaction** allTransactions = bankAccount->getAllTransactions();

    ASSERT_NE(allTransactions, nullptr);

    EXPECT_EQ(*(allTransactions), transactionOne);
    EXPECT_EQ(*(allTransactions + 1), transactionTwo);
}

TEST(AccountTest,
     GivenMultipleSavingsAccounts_WhenConstructed_ThenEachHasUniqueAccountNumber) {
    
    Account* bankAccountOne = new SavingsAccount();
    Account* bankAccountTwo = new CurrentAccount();
    Account* bankAccountThree = new SavingsAccount();

    long accountNumberOne = bankAccountOne->getAccountNumber();
    long accountNumberTwo = bankAccountTwo->getAccountNumber();
    long accountNumberThree = bankAccountThree->getAccountNumber();

    EXPECT_LT(accountNumberOne, accountNumberTwo);
    EXPECT_LT(accountNumberTwo, accountNumberThree);

    EXPECT_GT(accountNumberOne, Account::DEFAULT_ACC_NO + 1);
    EXPECT_GT(accountNumberTwo, Account::DEFAULT_ACC_NO + 2);
    EXPECT_GT(accountNumberThree, Account::DEFAULT_ACC_NO + 3);
}
