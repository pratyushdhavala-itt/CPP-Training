#include "gtest/gtest.h"
#include "input_validation.h"

#include "gtest/gtest.h"
#include "input_validation.h"

class UserIDValidationTest : public ::testing::TestWithParam<std::pair<std::string, bool>> {
protected:
    InputValidation validator;
};

TEST_P(UserIDValidationTest, GivenUserID_WhenValidated_ThenReturnsExpectedResult) {
    std::pair<std::string, bool> testCase = GetParam();
    EXPECT_EQ(validator.isValidUserID(testCase.first), testCase.second);
}

INSTANTIATE_TEST_SUITE_P(
    UserIDTests,
    UserIDValidationTest,
    ::testing::Values(
        std::make_pair("User123", true),       
        std::make_pair("abc_DEF", true),        
        std::make_pair("", false),              
        std::make_pair("a", false),             
        std::make_pair(std::string(50, 'a'), false),
        std::make_pair("User@123", false)      
    )
);

class PasswordValidationTest : public ::testing::TestWithParam<std::pair<std::string, bool>> {
protected:
    InputValidation validator;
};

TEST_P(PasswordValidationTest, GivenPassword_WhenValidated_ThenReturnsExpectedResult) {
    std::pair<std::string, bool> testCase = GetParam();
    EXPECT_EQ(validator.isValidPassword(testCase.first), testCase.second);
}

INSTANTIATE_TEST_SUITE_P(
    PasswordTests,
    PasswordValidationTest,
    ::testing::Values(
        std::make_pair("password1", true),
        std::make_pair("P@ssword123", true),
        std::make_pair("", false),
        std::make_pair("s", false),
        std::make_pair(std::string(50, 'a'), false),
        std::make_pair("has space", false)
    )
);

class AmountValidationTest : public ::testing::TestWithParam<std::pair<const char*, bool>> {
protected:
    InputValidation validator;
};

TEST_P(AmountValidationTest, GivenAmountString_WhenValidated_ThenReturnsExpectedResult) {
    std::pair<const char*, bool> testCase = GetParam();
    EXPECT_EQ(validator.isValidAmount(testCase.first), testCase.second);
}

INSTANTIATE_TEST_SUITE_P(
    AmountTests,
    AmountValidationTest,
    ::testing::Values(
        std::make_pair("123", true),       
        std::make_pair("123.45", true),    
        std::make_pair("", false),        
        std::make_pair("abc", false),      
        std::make_pair("12.3.4", false),   
        std::make_pair(nullptr, false)     
    )
);

class AccountNumberValidationTest : public ::testing::TestWithParam<std::pair<const char*, bool>> {
protected:
    InputValidation validator;
};

TEST_P(AccountNumberValidationTest, GivenAccountNumber_WhenValidated_ThenReturnsExpectedResult) {
    std::pair<const char*, bool> testCase = GetParam();
    EXPECT_EQ(validator.isValidAccountNumber(testCase.first), testCase.second);
}

INSTANTIATE_TEST_SUITE_P(
    AccountNumberTests,
    AccountNumberValidationTest,
    ::testing::Values(
        std::make_pair("1234", true),    
        std::make_pair("abcdef", false),  
        std::make_pair("12345", false),   
        std::make_pair("1234567", false),  
        std::make_pair("", false),        
        std::make_pair(nullptr, false)     
    )
);

class NameValidationTest : public ::testing::TestWithParam<std::pair<std::string, bool>> {
protected:
    InputValidation validator;
};

TEST_P(NameValidationTest, GivenUserName_WhenValidated_ThenReturnsExpectedResult) {
    std::pair<std::string, bool> testCase = GetParam();
    EXPECT_EQ(validator.isValidName(testCase.first), testCase.second);
}

INSTANTIATE_TEST_SUITE_P(
    NameTests,
    NameValidationTest,
    ::testing::Values(
        std::make_pair("John", true),     
        std::make_pair("jane", false),  
        std::make_pair("JOHN", false),    
        std::make_pair("JohnDoe", false), 
        std::make_pair("J", true),       
        std::make_pair("", false)        
    )
);

class MenuChoiceValidationTest : public ::testing::TestWithParam<std::pair<const char*, bool>> {
protected:
    InputValidation validator;
};

TEST_P(MenuChoiceValidationTest, GivenMenuChoiceInput_WhenValidated_ThenReturnsExpectedResult) {
    std::pair<const char*, bool> testCase = GetParam();
    EXPECT_EQ(validator.isValidMenuChoice(testCase.first), testCase.second);
}

INSTANTIATE_TEST_SUITE_P(
    MenuChoiceTests,
    MenuChoiceValidationTest,
    ::testing::Values(
        std::make_pair("1", true),     
        std::make_pair("2", true),   
        std::make_pair("0", false),    
        std::make_pair("3", false),   
        std::make_pair("", false),     
        std::make_pair(nullptr, false),
        std::make_pair("12", false),   
        std::make_pair("a", false)     
    )
);

class InputTooLongValidationTest : public ::testing::Test {
protected:
    InputValidation validator;
    std::streambuf* origCin;

    void SetUp() override {
        origCin = std::cin.rdbuf(); 
    }

    void TearDown() override {
        std::cin.rdbuf(origCin);
    }
};

TEST_F(InputTooLongValidationTest, GivenNormalInput_WhenChecked_ThenReturnsFalse) {
    std::istringstream input("123\n");
    std::cin.rdbuf(input.rdbuf());

    EXPECT_FALSE(validator.isInputTooLong());
}

TEST_F(InputTooLongValidationTest, GivenFailedCinState_WhenChecked_ThenReturnsTrueAndClearsFailState) {
    std::istringstream input(""); 
    std::cin.rdbuf(input.rdbuf());
    std::cin.setstate(std::ios::failbit);

    EXPECT_TRUE(validator.isInputTooLong());
    EXPECT_FALSE(std::cin.fail()); 
}
