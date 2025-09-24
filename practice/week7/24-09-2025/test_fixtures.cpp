#include <gtest/gtest.h>
#include "calculator.h"

class CalculatorTest : public ::testing::Test {

protected:
    Calculator calc;

public:

    void SetUp() {}

    void TearDown() {}

};

TEST_F(CalculatorTest, Addition) {
    EXPECT_EQ(calc.add(2, 3), 5);
    EXPECT_EQ(calc.add(-1, 1), 0);
}

TEST_F(CalculatorTest, Subtraction) {
    EXPECT_EQ(calc.sub(5, 3), 2);
}

TEST_F(CalculatorTest, DivisionByZero) {
    EXPECT_THROW(calc.divi(5, 0), std::invalid_argument);
}
