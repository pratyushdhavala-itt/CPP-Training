#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include "bank.h"

void performAdminBankOperation(Bank& bank);
void performCustomerBankOperation(Bank& bank);
void performDepositOperation(char (&inputDepositAmount)[9]);
#endif