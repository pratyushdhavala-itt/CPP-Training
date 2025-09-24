#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace std;

int main() {
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
}

class EmailService {
public:
    virtual ~EmailService() = default;
    virtual bool sendEmail(const std::string& msg) = 0;
};

class UserNotifier {
    EmailService* service;
public:
    UserNotifier(EmailService* s) : service(s) {}

    bool notifyNewUser() {
        return service->sendEmail("Welcome");
    }
};

class MockEmailService : public EmailService {
public:
    MOCK_METHOD(bool, sendEmail, (const std::string& msg), (override));
};

TEST(ServiceTest, SendEmailTest) {

    MockEmailService mockService;
    UserNotifier notifier(&mockService);

    EXPECT_CALL(mockService, sendEmail(::testing::_))
        .Times(1)
        .WillOnce(::testing::Return(true));

}