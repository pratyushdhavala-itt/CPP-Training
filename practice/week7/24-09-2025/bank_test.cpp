#include <iostream>
#include <gtest/gtest.h>
#include "bank_account.cpp"
using namespace std;

class BankTest : public ::testing::Test {

protected:
    BankAccount b;

public:

    void SetUp() {
        b = BankAccount(100);
    }

    void TearDown() {

    }
};

TEST_F(BankTest, Deposit) {
    b.deposit(50);
    EXPECT_EQ(b.getBalance(), 150);
}

TEST_F(BankTest, Withdraw) {
    
    EXPECT_TRUE(b.withdraw(40));
    EXPECT_EQ(b.getBalance(), 60);
}

TEST_F(BankTest, WithdrawalLimitTest) {
    EXPECT_FALSE(b.withdraw(101));
    EXPECT_EQ(b.getBalance(), 100);
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

