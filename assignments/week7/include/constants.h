#ifndef CONSTANTS_H
#define CONSTANTS_H

enum InputConstants {
    AMOUNT_INPUT = 9,
    MENU_INPUT = 2,
};

enum InputValidationConstants {
    PASSWORD_MIN_LENGTH = 4,
    PASSWORD_MAX_LENGTH = 20,
    USER_ID_MIN_LENGTH = 3,
    USER_ID_MAX_LENGTH = 20,
    IGNORE_CHARACTER_BUFFER = 1000,
    ACCOUNT_NO_LENGTH = 4,
    ARRAY_FIRST_INDEX = 0,
    INPUT_MENU_LENGTH = 1,
};

inline const char* PRINT_ENTER_USER_ID = "\nEnter user ID: ";
inline const char* PRINT_ENTER_PASSWORD = "\nEnter password: ";
inline const char* PRINT_ENTER_DEPOSIT_AMOUNT = "\nEnter the deposit amount: ";
inline const char* PRINT_ENTER_WITHDRAWAL_AMOUNT = "\nEnter the withdrawal amount: ";
inline const char* PRINT_DEPOSIT_SUCCESSFUL = "\nDeposit Successful";
inline const char* PRINT_DEPOSIT_FAILED = "\nDeposit Failed";
inline const char* PRINT_WITHDRAWAL_SUCCESSFUL = "\nWithdrawal Successful";
inline const char* PRINT_WITHDRAWAL_FAILED = "\nWithdrawal Failed";
inline const char* PRINT_ENTER_DEST_ACC_NO = "\nEnter the destination account number: ";
inline const char* PRINT_ENTER_TRANSFER_AMOUNT = "\nEnter the amount to be transferred: ";
inline const char* PRINT_TRANSFER_SUCCESSFUL = "\nTransfer Successful";
inline const char* PRINT_TRANSFER_FAILED = "\nTransfer Failed";
inline const char* PRINT_LOGOUT = "\nSuccessfully logged out ! ! !";
inline const char* PRINT_ENTER_USER_FIRST_NAME = "\nEnter User First Name: ";
inline const char* PRINT_ENTER_USER_LAST_NAME = "\nEnter User Last Name: ";
inline const char* PRINT_CREATE_ENTER_USER_ID = "\nEnter a User ID of your choice (alphanumeric): ";
inline const char* PRINT_CREATE_ENTER_USER_PASSWORD = "\nEnter a password of your choice (alphanumeric): ";
inline const char* PRINT_USER_CREATED = "\nUser successfully added ! ! !";
inline const char* PRINT_DELETE_USER_ID = "\nEnter the userID to be deleted: ";
inline const char* PRINT_USER_DELETED = "\nUser successfully deleted ! ! !";
inline const char* PRINT_LOGIN = "\nLogged in as: ";
inline const char* PRINT_CANNOT_DELETE_CURRENT_USER = "\nCannot delete current user ! ! ! Try again ! ! ! ";
inline const char* PRINT_USER_DOES_NOT_EXIST = "\nUser does not exist ! ! ! Try again ! ! ! ";
inline const char* PRINT_DEST_ACC_DOES_NOT_EXIST = "\nDestination account does not exist ! ! ! Try again ! ! ! ";
inline const char* PRINT_WRONG_PASSWORD = "\nEntered wrong password ! ! ! Try again ! ! !";
inline const char* PRINT_WRONG_USER_NAME = "\nUser name does not exist ! ! ! Try again ! ! ! ";
inline const char* PRINT_CURRENT_BALANCE = "\nYour current balance is: ";
inline const char* PRINT_INVALID_USER_FORMAT = "\nInvalid User ID format:-\n   1. User ID cannot be empty\n   2. User ID cannot be less than 3 characters\n   3. User ID cannot be more than 20 characters";
inline const char* PRINT_INVALID_PASSWORD_FORMAT = "\nInvalid password format:-\n   1. Password cannot contain blank spaces\n   2. Password cannot be less than 4 characters\n   3. Password cannot be more than 20 characters";
inline const char* PRINT_INVALID_AMOUNT_FORMAT = "\nInvalid format for amount.\n   1. Alphabets and special characters are not allowed\n   2. Maximum amount can be 9,99,99,999 only\n   3. Commas are not allowed"; 
inline const char* PRINT_INVALID_ACCOUNT_NO_FORMAT = "\nInvalid format for account number:-\n   1. Account number should be of four digits only\n   2. Account number should only consist of digits";
inline const char* PRINT_INVALID_USER_NAME_FORMAT = "\nInvalid User Name format ! ! !\n   1. First letter should always be capital\n   2. All other letters should be small\n   3. No spaces or empty input allowed";
inline const char* PRINT_WELCOME_BANK = "\nWelcome to the Bank ! ! !";
inline const char* PRINT_INPUT_TOO_LONG = "\nInput too long ! ! ! Try again ! ! !";
inline const char* PRINT_SELECT_USER_TYPE = "\nSelect from the below options:-\n   1. Admin\n   2. Customer\nYour option: ";
inline const char* PRINT_SELECT_ACCOUNT_TYPE = "\nSelect from the below options:-\n   1. Savings Account\n   2. Current Account\nYour option: ";
inline const char* PRINT_INVALID_INPUT = "\nInvalid input ! ! ! Try again ! ! !";
inline const char* PRINT_CUSTOMER_MENU = "\nPlease select your choice from the below options:-\n   1. Check Balance\n   2. Deposit\n   3. Withdraw\n   4. Transfer to another Account\n   5. Print Mini Statement\n   6. Print Full Statement\n   7. Any other key to Logout\nYour option: ";
inline const char* PRINT_LINE_SEPARATOR = "\n______________________________________";
inline const char* PRINT_OUTPUT_CUSTOMER_NAME = "Customer Name: ";
inline const char* PRINT_OUTPUT_CUSTOMER_ID = "Customer ID: ";
inline const char* PRINT_OUTPUT_CUSTOMER_ACC_ID = "Account Number: ";
inline const char* PRINT_OUTPUT_CUSTOMER_ACC_BALANCE = "Account Balance: ";
inline const char* PRINT_ADMIN_MENU = "\nPlease select your choice from the below options:-\n   1. Create New User\n   2. Delete Existing User\n   3. View All Users\n   4. Any other key to Logout\nYour option: ";
inline const char* PRINT_DEFAULT_ADMIN_NAME = "DEFAULT";
inline const char* PRINT_DEFAULT_ADMIN_LAST_NAME = "ADMIN";
inline const char* PRINT_DEFAULT_ADMIN_ID = "admin1";
inline const char* PRINT_DEFAULT_ADMIN_PASSWORD = "1234";
inline const char* PRINT_SLASH = "/";
inline const char* PRINT_COLON = ":";
inline const char* PRINT_SPACE = " ";
inline const char* PRINT_DEPOSIT = "DEPOSIT";
inline const char* PRINT_WITHDRAWAL = "WITHDRAWAL";
inline const char* PRINT_SENT_TRANSFER = "TRANSFER to Account Number: ";
inline const char* PRINT_RECD_TRANSFER = "TRANSFER from Account Number: ";
inline const char* PRINT_OUTPUT_TRANSACTION_TIMESTAMP = "Time Stamp: ";
inline const char* PRINT_OUTPUT_TRANSACTION_ID = "Transaction ID: ";
inline const char* PRINT_OUTPUT_TRANSACTION_TYPE = "Transaction Type: ";
inline const char* PRINT_OUTPUT_TRANSACTION_AMOUNT = "Amount: ";
inline const char* PRINT_OUTPUT_TRANSACTION_BALANCE = "Balance: ";
inline const char* PRINT_LOGIN_WELCOME = "\nWelcome ";
inline const char* PRINT_NEXT_LINE = "\n";
inline const char* PRINT_NO_CUSTOMER = "\nNo customers yet! ! !";
inline const char* PRINT_INSUFFICIENT_BALANCE = "\nInsufficient balance";
inline const char* PRINT_NO_SELF_TRANSFER = "\nCannot transfer to self";
inline const char* PRINT_CREATE_USER_WITH_ACCOUNT_NO = "Created User with Account Number: ";

#endif