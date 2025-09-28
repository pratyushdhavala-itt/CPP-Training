#include <gmock/gmock.h>
#include "authenticator.h"
#include "user.h"

class MockAuthenticator : public Authenticator {
public:
    MOCK_METHOD(AuthenticationState, getAuthenticationState, (), (override));
    MOCK_METHOD(AuthenticationErrorState, getAuthenticationErrorState, (), (override));
    MOCK_METHOD(AuthenticationState, authenticate,
                (const User::UserDetails& userOne, const User::UserDetails& userTwo), (override));
    MOCK_METHOD(void, unAuthenticate, (), (override));
    MOCK_METHOD(std::string, getLoginMessage, (), (const, override));
};