#include <gtest/gtest.h>
#include "customer.h"
#include "admin.h"
#include "user.h"
#include "mock_account.h"
#include "constants.h"


TEST(CustomerTest,
     GivenUserDetails_WhenCustomerConstructed_ThenUserDetailsInitialisedAndAccountIsNull) {

    User::UserDetails userDetails{"pratyushd", "my_password", "Pratyush", "Dhavala"};
    Customer customer(userDetails);

    EXPECT_EQ(customer.getAccount(), nullptr);
    EXPECT_EQ(customer.getUserType(), User::CUSTOMER);
    EXPECT_EQ(customer.getUserID(), "pratyushd");
    EXPECT_EQ(customer.getUserFullName(), "Pratyush Dhavala");
    EXPECT_EQ(customer.getPassword(), "my_password");
}

TEST(CustomerTest,
     GivenCustomer_WhenCreateAccountCalled_ThenAccountIsAssignedToCustomer) {

    User::UserDetails userDetails{"pratyushd", "my_password", "Pratyush", "Dhavala"};
    Customer customer(userDetails);

    MockAccount* mockAccount = new MockAccount();
    customer.createAccount(mockAccount);

    EXPECT_CALL(*mockAccount, getAccountType())
        .WillOnce(testing::Return(Account::SAVINGS_ACCOUNT));

    EXPECT_CALL(*mockAccount, getBalance())
        .WillOnce(testing::Return(Account::INITIAL_BALANCE));

    EXPECT_EQ(customer.getAccount(), mockAccount);
    EXPECT_EQ(customer.getAccount()->getAccountType(), Account::SAVINGS_ACCOUNT);
    EXPECT_EQ(customer.getAccount()->getBalance(), Account::INITIAL_BALANCE);
}

TEST(CustomerTest,
     GivenCustomer_WhenToStringCalled_ThenFormattedDetailsReturned) {
    
    User::UserDetails userDetails{"pratyushd", "my_password", "Pratyush", "Dhavala"};
    Customer customer(userDetails);

    MockAccount* mockAccount = new MockAccount();

    EXPECT_CALL(*mockAccount, getAccountNumber())
        .WillOnce(::testing::Return(1001));

    EXPECT_CALL(*mockAccount, getBalance())
        .WillOnce(::testing::Return(7000.0));

    customer.createAccount(mockAccount);

    std::string formattedString = customer.toString();

    std::string expectedFormattedString = std::string(PRINT_LINE_SEPARATOR) + '\n' +
           PRINT_OUTPUT_CUSTOMER_NAME + "Pratyush" + " " + "Dhavala" + '\n' +
           PRINT_OUTPUT_CUSTOMER_ID + "pratyushd" + '\n' +
           PRINT_OUTPUT_CUSTOMER_ACC_ID + "1001" + '\n' +
           PRINT_OUTPUT_CUSTOMER_ACC_BALANCE + "7000.000000";

    EXPECT_EQ(formattedString, expectedFormattedString);
}

TEST(AdminTest,
     GivenUserDetails_WhenAdminConstructed_ThenDetailsAndTypeAreCorrect) {
    
    User::UserDetails userDetails{"pratyushd", "my_password", "Pratyush", "Dhavala"};
    Admin admin(userDetails);

    EXPECT_EQ(admin.getUserID(), "pratyushd");
    EXPECT_EQ(admin.getPassword(), "my_password");
    EXPECT_EQ(admin.getUserType(), User::ADMIN);
    EXPECT_EQ(admin.getUserFullName(), "Pratyush Dhavala");
    EXPECT_EQ(admin.getAccount(), nullptr);
}

TEST(AdminTest,
     GivenMultipleAdmins_WhenConstructed_ThenEmployeeIDsAreUnique) {
    User::UserDetails userDetailsOne{"pratyushd", "my_password", "Pratyush", "Dhavala"};
    User::UserDetails userDetailsTwo{"praneyd", "my_password", "Praney", "Dhavala"};

    Admin admin1(userDetailsOne);
    Admin admin2(userDetailsTwo);

    EXPECT_NE(admin1.getEmployeeId(), admin2.getEmployeeId());
    EXPECT_EQ(admin1.getUserType(), User::ADMIN);
    EXPECT_EQ(admin2.getUserType(), User::ADMIN);

}
