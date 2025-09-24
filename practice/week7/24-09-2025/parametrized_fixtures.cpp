#include <iostream>
#include <gtest/gtest.h>

using namespace std;

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

class BankAccount {
    int balance;
public:
    BankAccount(int initial = 0) : balance(initial) {}
    int getBalance() const { return balance; }
};

struct AccountParams {
    int initialBalance;
    int expectedBalance;
};

class BankAccountTest : public ::testing::TestWithParam<AccountParams> {};

TEST_P(BankAccountTest, InitializesCorrectly) {
    AccountParams p = GetParam();
    BankAccount acc(p.initialBalance);
    EXPECT_EQ(acc.getBalance(), p.expectedBalance);
}

INSTANTIATE_TEST_SUITE_P(Balances, BankAccountTest,
    ::testing::Values(
        AccountParams{100, 100},
        AccountParams{0, 0},
        AccountParams{500, 500}
    ));
