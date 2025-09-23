#include <iostream>
#include <gtest/gtest.h>

using namespace std;

TEST(test1, sub1) {
    EXPECT_EQ(1, 2);
    cout << "This prints" << endl;
}

TEST(test1, sub2) {
    ASSERT_EQ(1, 2);
    cout << "this does not print" << endl;
}

int main() {
    
    testing::InitGoogleTest();
    
    return RUN_ALL_TESTS();
}