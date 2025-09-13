#include <iostream>

#include "authenticator.h"
#include "bank.h"
#include "constants.h"
#include "account.h"
#include "input_output.h"
#include "input_validation.h"



void takeInputAmount(double& amount, const char* inputMessage) {
    char inputAmount[9];
    while (true) {
        std::cout << inputMessage;
        std::cin.getline(inputAmount, 9);
        if (!InputValidation::isValidAmount(inputAmount)) {
            std::cout << PRINT_INVALID_AMOUNT_FORMAT << std::endl;
            continue;
        }
        break;
    }
    amount = atof(inputAmount);
}

void takeInputAccountNo(long& destinationAccountNo, const char* inputMessage) {
    char inputDestinationAccountNo[9];
    while (true) {
        std::cout << inputMessage;
        std::cin.getline(inputDestinationAccountNo, 9);
        if (!InputValidation::isValidAccountNumber(inputDestinationAccountNo)) {
            std::cout << PRINT_INVALID_ACCOUNT_NO_FORMAT << std::endl;
            continue;
        }
        break;
    }
    destinationAccountNo = atoi(inputDestinationAccountNo);
}

void takeInputUserMenu(int& input) {
    while(true) {
        char userInput[2];
        std::cin.getline(userInput, 2);
        if (InputValidation::isInputTooLong()) {
            std::cout << PRINT_INPUT_TOO_LONG << std::endl;
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

void performCustomerBankOperation(Bank& bank) { 
    while (true) {
        bank.showMenu();
        int input;
        takeInputUserMenu(input);
        double inputAmount;
        long destinationAccountNo;
        switch(input) {
            case Customer::BALANCE:
                std::cout << PRINT_CURRENT_BALANCE << bank.getCustomerBalance() << std::endl;
                break;
            case Customer::DEPOSIT:
                takeInputAmount(inputAmount, PRINT_ENTER_DEPOSIT_AMOUNT);
                bank.deposit(inputAmount);
                printTransactionStatus(bank.getCurrentTransactionState(), PRINT_DEPOSIT_SUCCESSFUL, PRINT_DEPOSIT_FAILED);
                break;
            case Customer::WITHDRAW:
                takeInputAmount(inputAmount, PRINT_ENTER_WITHDRAWAL_AMOUNT);
                bank.withdraw(inputAmount);
                printTransactionStatus(bank.getCurrentTransactionState(), PRINT_WITHDRAWAL_SUCCESSFUL, PRINT_WITHDRAWAL_FAILED);
                break;
            case Customer::TRANSFER:
                takeInputAccountNo(destinationAccountNo, PRINT_ENTER_DEST_ACC_NO);
                takeInputAmount(inputAmount, PRINT_ENTER_TRANSFER_AMOUNT);
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

void takeInputCreateUser(int& userTypeInput, std::string& userFirstName, std::string& userLastName, std::string& userID, std::string& userPassword, int& accountType) {
    char createUserInput[2];
    while (true) {
        std::cout << PRINT_SELECT_USER_TYPE << std::endl;
        std::cin.getline(createUserInput, 2);
        if (!InputValidation::isValidMenuChoice(createUserInput)) {
            std::cout << PRINT_INVALID_INPUT << std::endl;
            continue;
        }
        break;
    }
    userTypeInput = atoi(createUserInput);
    while (true) {
        std::cout << PRINT_ENTER_USER_FIRST_NAME;
        std::getline(std::cin, userFirstName);
        if (!InputValidation::isValidName(userFirstName)) {
            std::cout << PRINT_INVALID_USER_NAME_FORMAT << std::endl;
            continue;
        }
        break;
    }
    while (true) {
        std::cout << PRINT_ENTER_USER_LAST_NAME;
        std::getline(std::cin, userLastName);
        if (!InputValidation::isValidName(userLastName)) {
            std::cout << PRINT_INVALID_USER_NAME_FORMAT << std::endl;
            continue;
        }
        break;
    }
    while (true) {
        std::cout << PRINT_CREATE_ENTER_USER_ID;
        std::getline(std::cin, userID);
        if (!InputValidation::isValidUserID(userID)) {
            std::cout << PRINT_INVALID_USER_FORMAT << std::endl;
            continue;
        }
        break;
    }
    while (true) {
        std::cout << PRINT_CREATE_ENTER_USER_PASSWORD;
        std::getline(std::cin, userPassword);
        if (!InputValidation::isValidPassword(userPassword)) {
            std::cout << PRINT_INVALID_PASSWORD_FORMAT << std::endl;
            continue;
        }
        break;
    }
    char selectAccountType[2];
    while (true) {
        std::cout << PRINT_SELECT_ACCOUNT_TYPE << std::endl;
        std::cin.getline(selectAccountType, 2);
        if (!InputValidation::isValidMenuChoice(selectAccountType)) {
            std::cout << PRINT_INVALID_INPUT << std::endl;
        }
        break;
    }
    accountType = atoi(selectAccountType);
}

void takeInputDeleteUser(std::string& userID) {
    while (true) {
        std::cout << PRINT_DELETE_USER_ID;
        std::getline(std::cin, userID);
        if (!InputValidation::isValidUserID(userID)) {
            std::cout << PRINT_INVALID_USER_FORMAT << std::endl;
            continue;
        }
        break;
    }
}

void performAdminBankOperation(Bank& bank) {
    while (true) {
        bank.showMenu();
        int input;
        takeInputUserMenu(input);
        int userTypeInput;
        std::string userFirstName;
        std::string userLastName;
        std::string userID;
        std::string userPassword;
        int accountType;
        switch(input) {
            case Admin::CREATE_USER:
                takeInputCreateUser(userTypeInput, userFirstName, userLastName, userID, userPassword, accountType);
                if (userTypeInput == User::CUSTOMER) {
                    bank.addUser(userFirstName, userLastName, userID, userPassword, (Account::AccountType) accountType);
                } else {
                    bank.addUser(userFirstName, userLastName, userID, userPassword, Account::ADMIN_ACCOUNT);
                }
                std::cout << PRINT_USER_CREATED << std::endl;
                break;
            case Admin::DELETE_USER:
                takeInputDeleteUser(userID);
                bank.deleteUser(userID);
                if (bank.getCurrentTransactionState() == Bank::SUCCESS) {
                    std::cout << PRINT_USER_DELETED << std::endl;
                }
                break;
            case Admin::VIEW_ALL_CUSTOMERS:
                std::cout << bank.getAllCustomerDetails() << std::endl;
                break;
            default: 
                bank.logout();
                std::cout << PRINT_LOGOUT << std::endl;
                return;
        }
    }
}