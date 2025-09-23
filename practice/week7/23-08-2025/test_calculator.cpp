#include <gtest/gtest.h>
#include "calculator.h"

TEST(CalculatorTest, AdditionAndSubtraction) {
    Calculator c;
    EXPECT_EQ(c.add(2, 3), 5);
    EXPECT_EQ(c.sub(5, 3), 2);
}

TEST(CalculatorTest, Division) {
    Calculator c;
    EXPECT_EQ(c.divi(10, 2), 5);
    EXPECT_THROW(c.divi(1, 0), std::invalid_argument); 
}


TEST(StringTest, LargeStringCompare) {
    Calculator c;
    std::string s1 = c.repeat('a', 10000);  
    std::string s2 = s1;
    EXPECT_EQ(s1, s2); 
}

TEST(StringTest, CStringComparison) {
    const char* a = "hello";
    const char* b = "hello";
    EXPECT_STREQ(a, b);
}

int main() {

    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
