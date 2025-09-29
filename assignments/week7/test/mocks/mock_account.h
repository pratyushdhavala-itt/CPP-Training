#include <gmock/gmock.h>
#include "account.h"

class MockAccount : public Account {
public:
    MOCK_METHOD(double, getBalance, (), (const, override));
    MOCK_METHOD(void, setBalance, (double balance), (override));
    MOCK_METHOD(AccountType, getAccountType, (), (const, override));
    MOCK_METHOD(long, getAccountNumber, (), (const, override));
    MOCK_METHOD(int, getTransactionCount, (), (const, override));
    MOCK_METHOD(Transaction**, getAllTransactions, (), (const, override));
    MOCK_METHOD(void, addTransaction, (Transaction* t), (override));
};