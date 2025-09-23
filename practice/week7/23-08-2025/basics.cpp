#include <iostream>
#include <gtest/gtest.h>

TEST(testname, subtest_name) {
    ASSERT_TRUE(1 == 1);
}
TEST(testname, subtest_name_2) {
    ASSERT_TRUE(1 == 2);
}

TEST(testname2, subtest_name_2) {
    ASSERT_TRUE(1 == 2);
}

int main() {
    
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}