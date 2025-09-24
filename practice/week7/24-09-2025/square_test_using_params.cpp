#include <iostream>
#include <math.h>
#include <gtest/gtest.h>

using namespace std;

int main() {
    
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

int intSqrt(int n) {
    int r = std::sqrt(n);
    if (r * r != n) throw std::invalid_argument("not a perfect square");
    return r;
}

class SquareTest : public ::testing::TestWithParam<std::pair<int, int>>{};

TEST_P(SquareTest, getSquareRoot) {
    const std::pair<int, int>& p = GetParam();
    int input = p.first; 
    int expected = p.second;
    EXPECT_EQ(intSqrt(input), expected);
}

INSTANTIATE_TEST_SUITE_P(SqrtValues, SquareTest,
    ::testing::Values(
        std::make_pair(4, 2),
        std::make_pair(9, 3),
        std::make_pair(16, 4),
        std::make_pair(25, 5)
    )
);
