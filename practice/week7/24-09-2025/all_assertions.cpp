#include <iostream>
#include <gtest/gtest.h>

using namespace std;

int main() {
    
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}

TEST(test1, subtest1) {

    EXPECT_EQ(2 + 2, 4);
    EXPECT_NE(2 + 2, 5);
    EXPECT_LT(2, 5); 
    EXPECT_LE(5, 5); 
    EXPECT_GT(10, 5); 
    EXPECT_GE(10, 10); 

    EXPECT_TRUE(2 < 3);
    EXPECT_FALSE(2 > 3);

    EXPECT_FLOAT_EQ(0.3f, 0.1f + 0.2f); 
    EXPECT_DOUBLE_EQ(0.3, 0.1 + 0.2);   
    EXPECT_NEAR(3.1415, 3.14, 0.01);  

    std::string s = "hello";
    EXPECT_EQ(s, "hello");
    EXPECT_STREQ("hello", "hello"); 
    EXPECT_STRNE("hello", "world"); 
    EXPECT_STRCASEEQ("Hello", "HELLO"); 

    EXPECT_THROW(throw std::runtime_error("err"), std::runtime_error);
    EXPECT_ANY_THROW(throw 42);
    EXPECT_NO_THROW(int x = 5);

    double pi = 3.14159;
    EXPECT_NEAR(pi, 3.141, 0.001);

}