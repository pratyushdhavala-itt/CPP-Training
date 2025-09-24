#include <iostream>
#include <gtest/gtest.h>

using namespace std;

bool isEven(int n) {
    return n % 2 == 0;
}

class IsEvenTest : public ::testing::TestWithParam<int>{};

TEST_P(IsEvenTest, forEvenNumbers) {

    int n = GetParam();
    EXPECT_TRUE(isEven(n));
}

INSTANTIATE_TEST_SUITE_P(Evens, IsEvenTest, ::testing::Values(2, 4, 6, 100, 500));

TEST_P(IsEvenTest, forOddNumbers) {
    int n = GetParam();
    EXPECT_FALSE(isEven(n));
}

INSTANTIATE_TEST_SUITE_P(Odds, IsEvenTest, ::testing::Values(1, 3, 9, 99, 101));
int main() {
    
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}