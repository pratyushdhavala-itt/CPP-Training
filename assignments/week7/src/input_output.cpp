#include <iostream>

#include "authenticator.h"
#include "bank.h"
#include "constants.h"
#include "account.h"
#include "input_output.h"
#include "input_validation.h"
#include "user.h"


void takeInputAmount(InputValidation& inputValidation, double& amount, const char* inputMessage) {
    char inputAmount[AMOUNT_INPUT];
    while (true) {
        std::cout << inputMessage;
        std::cin.getline(inputAmount, AMOUNT_INPUT);
        if (!inputValidation.isValidAmount(inputAmount)) {
            std::cout << PRINT_INVALID_AMOUNT_FORMAT << std::endl;
            continue;
        }
        break;
    }
    amount = atof(inputAmount);
}

void takeInputAccountNo(InputValidation& inputValidation, long& destinationAccountNo, const char* inputMessage) {
    char inputDestinationAccountNo[AMOUNT_INPUT];
    while (true) {
        std::cout << inputMessage;
        std::cin.getline(inputDestinationAccountNo, AMOUNT_INPUT);
        if (!inputValidation.isValidAccountNumber(inputDestinationAccountNo)) {
            std::cout << PRINT_INVALID_ACCOUNT_NO_FORMAT << std::endl;
            continue;
        }
        break;
    }
    destinationAccountNo = atoi(inputDestinationAccountNo);
}

void takeInputUserMenu(InputValidation& inputValidation, int& input) {
    while(true) {
        char userInput[2];
        std::cin.getline(userInput, MENU_INPUT);
        if (inputValidation.isInputTooLong()) {
            std::cout << PRINT_INPUT_TOO_LONG << std::endl;
            std::cin.ignore(IGNORE_CHARACTER_BUFFER, '\n');
            continue;
        }
        input = atoi(userInput);
        break;
    }
}

void printTransactionStatus(Bank::TransactionState transactionState, const char* successMessage, const char* failureMessage) {
    if (transactionState == Bank::SUCCESS) {
        std::cout << successMessage << std::endl;
    } else {
        std::cout << failureMessage << std::endl;
    }
}

void performCustomerBankOperation(Bank& bank, InputValidation& inputValidation) { 
    while (true) {
        bank.showMenu();
        int input;
        takeInputUserMenu(inputValidation, input);
        double inputAmount;
        long destinationAccountNo;
        switch(input) {
            case Customer::BALANCE:
                std::cout << PRINT_CURRENT_BALANCE << bank.getCustomerBalance() << std::endl;
                break;
            case Customer::DEPOSIT:
                takeInputAmount(inputValidation, inputAmount, PRINT_ENTER_DEPOSIT_AMOUNT);
                bank.deposit(inputAmount);
                printTransactionStatus(bank.getCurrentTransactionState(), PRINT_DEPOSIT_SUCCESSFUL, PRINT_DEPOSIT_FAILED);
                break;
            case Customer::WITHDRAW:
                takeInputAmount(inputValidation, inputAmount, PRINT_ENTER_WITHDRAWAL_AMOUNT);
                bank.withdraw(inputAmount);
                printTransactionStatus(bank.getCurrentTransactionState(), PRINT_WITHDRAWAL_SUCCESSFUL, PRINT_WITHDRAWAL_FAILED);
                break;
            case Customer::TRANSFER:
                takeInputAccountNo(inputValidation, destinationAccountNo, PRINT_ENTER_DEST_ACC_NO);
                takeInputAmount(inputValidation, inputAmount, PRINT_ENTER_TRANSFER_AMOUNT);
                bank.transfer(destinationAccountNo, inputAmount);
                printTransactionStatus(bank.getCurrentTransactionState(), PRINT_TRANSFER_SUCCESSFUL, PRINT_TRANSFER_FAILED);
                break;
            case Customer::MINI_STATEMENT: 
                std::cout << bank.getAccountMiniStatement() << std::endl;
                break;
            case Customer::FULL_STATEMENT:
                std::cout << bank.getAccountFullStatement() << std::endl;
                break;
            default:
                bank.logout();
                std::cout << PRINT_LOGOUT << std::endl;
                return;
        }
    }
}

void takeInputCreateUser(InputValidation& inputValidation, int& userTypeInput, User::UserDetails& inputUserDetails, int& accountType) {
    char createUserInput[MENU_INPUT];
    while (true) {
        std::cout << PRINT_SELECT_USER_TYPE << std::endl;
        std::cin.getline(createUserInput, MENU_INPUT);
        if (!inputValidation.isValidMenuChoice(createUserInput)) {
            std::cout << PRINT_INVALID_INPUT << std::endl;
            continue;
        }
        break;
    }
    userTypeInput = atoi(createUserInput);
    while (true) {
        std::cout << PRINT_ENTER_USER_FIRST_NAME;
        std::getline(std::cin, inputUserDetails.userFirstName);
        if (!inputValidation.isValidName(inputUserDetails.userFirstName)) {
            std::cout << PRINT_INVALID_USER_NAME_FORMAT << std::endl;
            continue;
        }
        break;
    }
    while (true) {
        std::cout << PRINT_ENTER_USER_LAST_NAME;
        std::getline(std::cin, inputUserDetails.userLastName);
        if (!inputValidation.isValidName(inputUserDetails.userLastName)) {
            std::cout << PRINT_INVALID_USER_NAME_FORMAT << std::endl;
            continue;
        }
        break;
    }
    while (true) {
        std::cout << PRINT_CREATE_ENTER_USER_ID;
        std::getline(std::cin, inputUserDetails.userId);
        if (!inputValidation.isValidUserID(inputUserDetails.userId)) {
            std::cout << PRINT_INVALID_USER_FORMAT << std::endl;
            continue;
        }
        break;
    }
    while (true) {
        std::cout << PRINT_CREATE_ENTER_USER_PASSWORD;
        std::getline(std::cin, inputUserDetails.userPassword);
        if (!inputValidation.isValidPassword(inputUserDetails.userPassword)) {
            std::cout << PRINT_INVALID_PASSWORD_FORMAT << std::endl;
            continue;
        }
        break;
    }
    char selectAccountType[MENU_INPUT];
    while (true && userTypeInput != User::ADMIN) {
        std::cout << PRINT_SELECT_ACCOUNT_TYPE << std::endl;
        std::cin.getline(selectAccountType, MENU_INPUT);
        if (!inputValidation.isValidMenuChoice(selectAccountType)) {
            std::cout << PRINT_INVALID_INPUT << std::endl;
            continue;
        }
        break;
    }
    accountType = atoi(selectAccountType);
}

void takeInputDeleteUser(InputValidation& inputValidation, User::UserDetails& inputUserDetails) {
    while (true) {
        std::cout << PRINT_DELETE_USER_ID;
        std::getline(std::cin, inputUserDetails.userId);
        if (!inputValidation.isValidUserID(inputUserDetails.userId)) {
            std::cout << PRINT_INVALID_USER_FORMAT << std::endl;
            continue;
        }
        break;
    }
}

void performAdminBankOperation(Bank& bank, InputValidation& inputValidation) {
    while (true) {
        bank.showMenu();
        int input;
        takeInputUserMenu(inputValidation ,input);
        int userTypeInput;
        User::UserDetails inputUserDetails;
        int accountType;
        switch(input) {
            case Admin::CREATE_USER: {
                takeInputCreateUser(inputValidation, userTypeInput, inputUserDetails, accountType);
                if (userTypeInput == User::CUSTOMER) {
                    User* newCustomer = bank.createUser(inputUserDetails, (Account::AccountType) accountType);
                    bank.addUser(newCustomer);
                } else {
                    User* newAdmin = bank.createUser(inputUserDetails, Account::ADMIN_ACCOUNT);
                    bank.addUser(newAdmin);
                }
                std::cout << PRINT_USER_CREATED << std::endl;
                break;
            }
            case Admin::DELETE_USER: {
                takeInputDeleteUser(inputValidation, inputUserDetails);
                bank.deleteUser(inputUserDetails);
                if (bank.getCurrentTransactionState() == Bank::SUCCESS) {
                    std::cout << PRINT_USER_DELETED << std::endl;
                }
                break;
            }
            case Admin::VIEW_ALL_CUSTOMERS: {
                std::cout << bank.getAllCustomerDetails() << std::endl;
                break;
            }
            default: {
                bank.logout();
                std::cout << PRINT_LOGOUT << std::endl;
                return;
            }
        }
    }
}