#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <iostream>
#include <string>
#include <input_output.h>
#include "constants.h"
#include "input_validation.h"
#include "mock_input_validation.h"
#include "mock_bank.h"

class TakeInputTest : public ::testing::Test {
protected:
    std::stringstream testInput;
    std::stringstream testOutput;
    std::streambuf* originalInputBuffer;
    std::streambuf* originalOutputBuffer;
    MockInputValidation* mockInputValidation;
    MockBank* mockBank;

    void SetUp() override {

        mockBank = new MockBank();
        mockInputValidation = new MockInputValidation();

        originalInputBuffer = std::cin.rdbuf(testInput.rdbuf());
        originalOutputBuffer = std::cout.rdbuf(testOutput.rdbuf());
    }

    void TearDown() override {
        std::cin.rdbuf(originalInputBuffer);
        std::cout.rdbuf(originalOutputBuffer);
        delete mockInputValidation;
        delete mockBank;
    }
};

TEST_F(TakeInputTest, GivenInvalidInputThenValidInput_WhenTakeInputAmount_ThenStoresValidAmountWithErrorMessage) {

    testInput << "abc\n123.45\n";
    double amount = 0.0;

    EXPECT_CALL(*mockInputValidation, isValidAmount(testing::_))
        .WillOnce(testing::Return(false))  
        .WillOnce(testing::Return(true));  

    takeInputAmount(*mockInputValidation, amount, "Enter amount: ");

    EXPECT_DOUBLE_EQ(amount, 123.45);

    std::string output = testOutput.str();
    EXPECT_THAT(output, testing::HasSubstr(PRINT_INVALID_AMOUNT_FORMAT));
}

TEST_F(TakeInputTest, GivenValidInput_WhenTakeInputAmount_ThenStoresAmountWithoutErrorMessage) {
    
    testInput << "987.65\n";
    double amount = 0.0;

    EXPECT_CALL(*mockInputValidation, isValidAmount(testing::_))
        .WillOnce(testing::Return(true));  

    takeInputAmount(*mockInputValidation, amount, "Enter amount: ");

    EXPECT_DOUBLE_EQ(amount, 987.65);
}

TEST_F(TakeInputTest, GivenInvalidThenValidInput_WhenTakeInputAccountNo_ThenStoresValidAccountNoWithErrorMessage) {
    
    testInput << "abcd\n1234\n";
    long accNo = 0;

    EXPECT_CALL(*mockInputValidation, isValidAccountNumber(testing::_))
        .WillOnce(testing::Return(false))
        .WillOnce(testing::Return(true));  

    takeInputAccountNo(*mockInputValidation, accNo, "Enter account no: ");

    EXPECT_EQ(accNo, 1234);

    std::string output = testOutput.str();
    EXPECT_THAT(output, testing::HasSubstr(PRINT_INVALID_ACCOUNT_NO_FORMAT));
}

TEST_F(TakeInputTest, GivenValidInput_WhenTakeInputAccountNo_ThenStoresAccountNoWithoutErrorMessage) {
    
    testInput << "9876\n";
    long accNo = 0;

    EXPECT_CALL(*mockInputValidation, isValidAccountNumber(testing::_))
        .WillOnce(testing::Return(true)); 

    takeInputAccountNo(*mockInputValidation, accNo, "Enter account no: ");

    EXPECT_EQ(accNo, 9876);
}

TEST_F(TakeInputTest, GivenTooLongInputThenValidInput_WhenTakeInputUserMenu_ThenStoresValidMenuChoiceWithError) {

    testInput << "123\n4\n";
    int menuChoice = 0;

    EXPECT_CALL(*mockInputValidation, isInputTooLong())
        .WillOnce(testing::Return(true))  
        .WillOnce(testing::Return(false)); 

    takeInputUserMenu(*mockInputValidation, menuChoice);

    std::string output = testOutput.str();
    EXPECT_EQ(menuChoice, 0);
    EXPECT_THAT(output, testing::HasSubstr(PRINT_INPUT_TOO_LONG));
}

TEST_F(TakeInputTest, GivenValidInput_WhenTakeInputUserMenu_ThenStoresChoiceWithoutErrorMessage) {
    
    testInput << "7\n";
    int menuChoice = 0;

    EXPECT_CALL(*mockInputValidation, isInputTooLong())
        .WillOnce(testing::Return(false));

    takeInputUserMenu(*mockInputValidation, menuChoice);

    EXPECT_EQ(menuChoice, 7);
}

TEST_F(TakeInputTest, GivenDepositChoice_WhenPerformOperation_ThenDepositIsCalledAndThenLogout) {

    testInput << "2\n1000\n0\n";

    EXPECT_CALL(*mockInputValidation, isInputTooLong())
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(*mockInputValidation, isValidAmount(testing::_))
        .WillOnce(testing::Return(true)); 

    EXPECT_CALL(*mockBank, showMenu()).Times(2);  
    EXPECT_CALL(*mockBank, deposit(1000)).Times(1);
    EXPECT_CALL(*mockBank, logout()).Times(1);

    EXPECT_CALL(*mockBank, getCurrentTransactionState())
      .WillRepeatedly(testing::Return(Bank::SUCCESS));

 
    performCustomerBankOperation(*mockBank, *mockInputValidation);
    std::string output = testOutput.str();
    EXPECT_THAT(output, ::testing::HasSubstr(PRINT_DEPOSIT_SUCCESSFUL));
}

TEST_F(TakeInputTest, GivenWithdrawChoice_WhenPerformOperation_ThenWithdrawIsCalledAndThenLogout) {

    testInput << "3\n500\n0\n";

    EXPECT_CALL(*mockInputValidation, isInputTooLong())
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(*mockInputValidation, isValidAmount(testing::_))
        .WillOnce(testing::Return(true)); 
    
    EXPECT_CALL(*mockBank, showMenu()).Times(2);        
    EXPECT_CALL(*mockBank, withdraw(500)).Times(1);     
    EXPECT_CALL(*mockBank, logout()).Times(1);          
    EXPECT_CALL(*mockBank, getCurrentTransactionState())
        .WillRepeatedly(testing::Return(Bank::SUCCESS));        

    performCustomerBankOperation(*mockBank, *mockInputValidation);
    std::string output = testOutput.str();
    EXPECT_THAT(output, ::testing::HasSubstr(PRINT_WITHDRAWAL_SUCCESSFUL));
}

TEST_F(TakeInputTest, GivenTransferChoice_WhenPerformOperation_ThenTransferIsCalledAndThenLogout) {
   
    testInput << "4\n1234\n750\n0\n";

    EXPECT_CALL(*mockInputValidation, isInputTooLong())
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(*mockInputValidation, isValidAccountNumber(testing::_))
        .WillOnce(testing::Return(true));   

    EXPECT_CALL(*mockInputValidation, isValidAmount(testing::_))
        .WillOnce(testing::Return(true));   

    EXPECT_CALL(*mockBank, showMenu()).Times(2);             
    EXPECT_CALL(*mockBank, transfer(1234, 750)).Times(1);   
    EXPECT_CALL(*mockBank, logout()).Times(1);               
    EXPECT_CALL(*mockBank, getCurrentTransactionState())
        .WillRepeatedly(testing::Return(Bank::SUCCESS));            

    performCustomerBankOperation(*mockBank, *mockInputValidation);
    std::string output = testOutput.str();
    EXPECT_THAT(output, ::testing::HasSubstr(PRINT_TRANSFER_SUCCESSFUL));
}

TEST_F(TakeInputTest, GivenBalanceChoice_WhenPerformOperation_ThenBalanceIsPrintedAndThenLogout) {

    testInput << "1\n0\n";

    EXPECT_CALL(*mockInputValidation, isInputTooLong())
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(*mockBank, showMenu()).Times(2);            
    EXPECT_CALL(*mockBank, getCustomerBalance())
        .WillOnce(testing::Return(5000.0));                         
    EXPECT_CALL(*mockBank, logout()).Times(1);

    performCustomerBankOperation(*mockBank, *mockInputValidation);
}

TEST_F(TakeInputTest, GivenMiniStatementChoice_WhenPerformOperation_ThenMiniStatementIsPrintedAndThenLogout) {

    testInput << "5\n0\n";

    EXPECT_CALL(*mockInputValidation, isInputTooLong())
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(*mockBank, showMenu()).Times(2);                      
    EXPECT_CALL(*mockBank, getAccountMiniStatement())
        .WillOnce(testing::Return("MiniStatementPrintedHere"));                     
    EXPECT_CALL(*mockBank, logout()).Times(1);
 
    performCustomerBankOperation(*mockBank, *mockInputValidation);
    std::string output = testOutput.str();
    EXPECT_THAT(output, ::testing::HasSubstr("MiniStatementPrintedHere"));
}

TEST_F(TakeInputTest, GivenFullStatementChoice_WhenPerformOperation_ThenFullStatementIsPrintedAndThenLogout) {

    testInput << "6\n0\n";

    EXPECT_CALL(*mockInputValidation, isInputTooLong())
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(*mockBank, showMenu()).Times(2);                          
    EXPECT_CALL(*mockBank, getAccountFullStatement())
        .WillOnce(testing::Return("FullStatementPrintedHere"));                       
    EXPECT_CALL(*mockBank, logout()).Times(1);

    performCustomerBankOperation(*mockBank, *mockInputValidation);
    std::string output = testOutput.str();
    EXPECT_THAT(output, testing::HasSubstr("FullStatementPrintedHere"));
}

TEST_F(TakeInputTest, GivenCreateCustomerUserChoice_WhenPerformOperation_ThenUserIsCreatedAndThenLogout) {

    testInput << "1\n1\nPratyush\nDhavala\nprat\nmy_password\n0\n";

    EXPECT_CALL(*mockInputValidation, isInputTooLong())
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(*mockInputValidation, isValidMenuChoice(testing::_))
        .WillRepeatedly(testing::Return(true));

    EXPECT_CALL(*mockInputValidation, isValidName(testing::_))
        .WillRepeatedly(testing::Return(true));

    EXPECT_CALL(*mockInputValidation, isValidUserID(testing::_))
        .WillRepeatedly(testing::Return(true));

    EXPECT_CALL(*mockInputValidation, isValidPassword(testing::_))
        .WillRepeatedly(testing::Return(true));

    EXPECT_CALL(*mockBank, showMenu()).Times(2); 
    EXPECT_CALL(*mockBank, createUser(testing::_, testing::_))
        .WillOnce(testing::Return(new Customer({"prat", "my_password", "Pratyush", "Dhavala"}))); 
    EXPECT_CALL(*mockBank, addUser(testing::_)).Times(1);
    EXPECT_CALL(*mockBank, logout()).Times(1);

    performAdminBankOperation(*mockBank, *mockInputValidation);
    std::string output = testOutput.str();
    EXPECT_THAT(output, ::testing::HasSubstr(PRINT_USER_CREATED));
}

TEST_F(TakeInputTest, GivenDeleteUserChoice_WhenPerformOperation_ThenUserIsDeletedAndThenLogout) {

    testInput << "2\nprat\n0\n";

    EXPECT_CALL(*mockInputValidation, isInputTooLong())
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(*mockBank, showMenu()).Times(2);
    EXPECT_CALL(*mockInputValidation, isValidUserID(testing::_))
        .WillOnce(testing::Return(true));
    EXPECT_CALL(*mockBank, deleteUser(testing::_)).Times(1);
    EXPECT_CALL(*mockBank, getCurrentTransactionState())
        .WillOnce(testing::Return(Bank::SUCCESS));
    EXPECT_CALL(*mockBank, logout()).Times(1);

    performAdminBankOperation(*mockBank, *mockInputValidation);
    std::string output = testOutput.str();
    EXPECT_THAT(output, ::testing::HasSubstr(PRINT_USER_DELETED));
}

TEST_F(TakeInputTest, GivenViewAllCustomersChoice_WhenPerformOperation_ThenAllCustomerDetailsArePrintedAndThenLogout) {

    testInput << "3\n0\n";

    EXPECT_CALL(*mockInputValidation, isInputTooLong())
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(*mockBank, showMenu()).Times(2);
    EXPECT_CALL(*mockBank, getAllCustomerDetails())
        .WillOnce(testing::Return("Customer1\nCustomer2"));
    EXPECT_CALL(*mockBank, logout()).Times(1);

    performAdminBankOperation(*mockBank, *mockInputValidation);
    std::string output = testOutput.str();
    EXPECT_THAT(output, ::testing::HasSubstr("Customer1"));
    EXPECT_THAT(output, ::testing::HasSubstr("Customer2"));
}

TEST_F(TakeInputTest, GivenInvalidChoice_WhenPerformOperation_ThenLogoutImmediately) {

    testInput << "9\n";

    EXPECT_CALL(*mockInputValidation, isInputTooLong())
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(*mockBank, showMenu()).Times(1);
    EXPECT_CALL(*mockBank, logout()).Times(1);

    performAdminBankOperation(*mockBank, *mockInputValidation);
    std::string output = testOutput.str();
    EXPECT_THAT(output, testing::HasSubstr(PRINT_LOGOUT));
}

TEST_F(TakeInputTest, GivenValidInputs_WhenTakeInputCreateUser_ThenDetailsAreStoredCorrectly) {

    testInput << "2\nPratyush\nDhavala\nprat\n1234\n1\n";

    int userTypeInput;
    User::UserDetails userDetails;
    int accountType;

    EXPECT_CALL(*mockInputValidation, isValidMenuChoice(testing::_))
        .Times(2) 
        .WillRepeatedly(testing::Return(true));

    EXPECT_CALL(*mockInputValidation, isValidName(testing::_))
        .Times(2) 
        .WillRepeatedly(testing::Return(true));

    EXPECT_CALL(*mockInputValidation, isValidUserID(testing::_))
        .Times(1)
        .WillOnce(testing::Return(true));

    EXPECT_CALL(*mockInputValidation, isValidPassword(testing::_))
        .Times(1)
        .WillOnce(testing::Return(true));

    takeInputCreateUser(*mockInputValidation, userTypeInput, userDetails, accountType);

    EXPECT_EQ(userTypeInput, User::CUSTOMER);
    EXPECT_EQ(userDetails.userFirstName, "Pratyush");
    EXPECT_EQ(userDetails.userLastName, "Dhavala");
    EXPECT_EQ(userDetails.userId, "prat");
    EXPECT_EQ(userDetails.userPassword, "1234");
    EXPECT_EQ(accountType, Account::SAVINGS_ACCOUNT);
}
