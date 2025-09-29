#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include "input_validation.h"
#include "bank.h"

void performAdminBankOperation(Bank& bank, InputValidation& inputValidation);
void performCustomerBankOperation(Bank& bank, InputValidation& inputValidation);
void takeInputAmount(InputValidation& inputValidation, double& amount, const char* inputMessage);
void takeInputAccountNo(InputValidation& inputValidation, long& destinationAccountNo, const char* inputMessage);
void takeInputUserMenu(InputValidation& inputValidation, int& input);
void printTransactionStatus(Bank::TransactionState transactionState, const char* successMessage, const char* failureMessage);
void takeInputCreateUser(InputValidation& inputValidation, int& userTypeInput, User::UserDetails& inputUserDetails, int& accountType);
void takeInputDeleteUser(InputValidation& inputValidation, User::UserDetails& inputUserDetails);

#endif