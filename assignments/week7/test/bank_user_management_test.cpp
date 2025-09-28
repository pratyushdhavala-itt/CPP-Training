#include "gtest/gtest.h"
#include "bank.h"
#include "customer.h"
#include "admin.h"
#include "constants.h"

class BankUserTest : public ::testing::Test {
protected:
    Bank* bank;
    User::UserDetails userDetails;

    void SetUp() override {
        bank = &Bank::getBankInstance(nullptr);
        User* defaultAdmin = bank->getUserById("admin1");
        bank->setCurrentUser(defaultAdmin);
        userDetails = {"pratyushd", "my_password", "Pratyush", "Dhavala"};
    }

    void TearDown() override {
        bank->reset();
    }
};

TEST_F(BankUserTest,
       GivenAdminDetails_WhenCreateUserCalled_ThenAdminUserIsCreated) {

    User* adminUser = bank->createUser(userDetails, Account::ADMIN_ACCOUNT);

    ASSERT_NE(adminUser, nullptr);
    EXPECT_EQ(adminUser->getUserType(), User::ADMIN);
    EXPECT_EQ(adminUser->getUserID(), userDetails.userId);
    EXPECT_EQ(adminUser->getUserFullName(), "Pratyush Dhavala");

    delete adminUser; 
}

TEST_F(BankUserTest,
       GivenCustomerDetailsWithSavingsAccount_WhenCreateUserCalled_ThenCustomerWithSavingsAccountIsCreated) {

    User* customer = bank->createUser(userDetails, Account::SAVINGS_ACCOUNT);
    Account* customerAccount = customer->getAccount();

    ASSERT_NE(customer, nullptr);
    EXPECT_EQ(customer->getUserType(), User::CUSTOMER);
    EXPECT_EQ(customer->getUserID(), userDetails.userId);
    EXPECT_EQ(customer->getUserFullName(), userDetails.userFirstName + " " + userDetails.userLastName);
    ASSERT_NE(customerAccount, nullptr);
    EXPECT_EQ(customerAccount->getAccountType(), Account::SAVINGS_ACCOUNT);
    EXPECT_EQ(customerAccount->getBalance(), Account::INITIAL_BALANCE);

    delete customer;
}

TEST_F(BankUserTest,
       GivenCustomerDetailsWithCurrentAccount_WhenCreateUserCalled_ThenCustomerWithCurrentAccountIsCreated) {

    User* customer = bank->createUser(userDetails, Account::CURRENT_ACCOUNT);
    Account* customerAccount = customer->getAccount();

    ASSERT_NE(customer, nullptr);
    EXPECT_EQ(customer->getUserType(), User::CUSTOMER);
    EXPECT_EQ(customer->getUserID(), userDetails.userId);
    EXPECT_EQ(customer->getUserFullName(), userDetails.userFirstName + " " + userDetails.userLastName);
    ASSERT_NE(customerAccount, nullptr);
    EXPECT_EQ(customerAccount->getAccountType(), Account::CURRENT_ACCOUNT);
    EXPECT_EQ(customerAccount->getBalance(), Account::INITIAL_BALANCE);

    delete customer;
}

TEST_F(BankUserTest,
       GivenNewCustomer_WhenAddUserCalled_ThenUserIsAddedToBank) {

    User* customer = bank->createUser(userDetails, Account::SAVINGS_ACCOUNT);

    bank->addUser(customer);

    User* foundUser = bank->getUserById(userDetails.userId);
    ASSERT_NE(foundUser, nullptr);
    EXPECT_EQ(foundUser->getUserID(), userDetails.userId);
    EXPECT_EQ(foundUser->getUserFullName(), userDetails.userFirstName + " " + userDetails.userLastName);
}

TEST_F(BankUserTest,
       GivenNonExistentUserId_WhenGetUserByIdCalled_ThenNullptrIsReturned) {

    User* foundUser = bank->getUserById("praneyd");

    EXPECT_EQ(foundUser, nullptr);
}

TEST_F(BankUserTest,
       GivenUserId_WhenGetUserIndexCalled_ThenReturnUserIndex) {

    User* customer = bank->createUser(userDetails, Account::SAVINGS_ACCOUNT);
    bank->addUser(customer);

    int userIndex = bank->getUserIndex(userDetails.userId);

    EXPECT_GT(userIndex, 0);
}

TEST_F(BankUserTest,
       GivenWrongUserId_WhenGetUserIndexCalled_ThenReturnMinusOne) {

    std::string userId = "praneyd";
    int userIndex = bank->getUserIndex(userId);

    EXPECT_EQ(userIndex, -1);
}

TEST_F(BankUserTest,
       GivenExistingUser_WhenDeleteUserCalled_ThenUserIsRemovedFromBank) {

    User* customer = bank->createUser(userDetails, Account::SAVINGS_ACCOUNT);
    bank->addUser(customer);

    ASSERT_NE(bank->getUserById(userDetails.userId), nullptr);

    bank->deleteUser(userDetails);

    EXPECT_EQ(bank->getUserById(userDetails.userId), nullptr);
}

TEST_F(BankUserTest,
       GivenCurrentUser_WhenDeleteUserCalled_ThenUserIsNotDeleted) {

    User* customer = bank->createUser(userDetails, Account::SAVINGS_ACCOUNT);
    bank->addUser(customer);
    bank->setCurrentUser(customer);

    bank->deleteUser(userDetails);

    EXPECT_NE(bank->getUserById(userDetails.userId), nullptr); 
}

TEST_F(BankUserTest,
       GivenExistingCustomers_WhenGetAllCustomerDetailsCalled_ThenSomethingIsReturned) {

    User* customer = bank->createUser(userDetails, Account::SAVINGS_ACCOUNT);
    bank->addUser(customer);

    std::string details = bank->getAllCustomerDetails();
    
    EXPECT_NE(details, "");
}

TEST_F(BankUserTest,
       GivenNoCustomers_WhenGetAllCustomerDetailsCalled_ThenNothingIsReturned) {

    std::string details = bank->getAllCustomerDetails();
    
    EXPECT_STREQ(details.c_str(), PRINT_NO_CUSTOMER);
}

TEST_F(BankUserTest,
       GivenCustomer_WhenSetCurrentUserCalled_ThenCurrentUserAndTypeAreUpdated) {

    User* customer = bank->createUser(userDetails, Account::SAVINGS_ACCOUNT);
    bank->addUser(customer);

    bank->setCurrentUser(customer);

    EXPECT_EQ(bank->getCurrentUser(), customer);
    EXPECT_EQ(bank->getUserType(), User::CUSTOMER);
}

TEST_F(BankUserTest,
       GivenAdmin_WhenSetCurrentUserCalled_ThenCurrentUserAndTypeAreUpdated) {

    User* adminUser = bank->createUser(userDetails, Account::ADMIN_ACCOUNT);
    bank->addUser(adminUser);

    bank->setCurrentUser(adminUser);

    EXPECT_EQ(bank->getCurrentUser(), adminUser);
    EXPECT_EQ(bank->getUserType(), User::ADMIN);
}

