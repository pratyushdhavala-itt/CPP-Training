#include <iostream>
#include <string>

#include "admin.h"
#include "constants.h"

int Admin::adminCount = 1;

Admin::Admin() 
    : User(PRINT_DEFAULT_ADMIN_NAME, 
           PRINT_DEFAULT_ADMIN_LAST_NAME, 
           PRINT_DEFAULT_ADMIN_ID, 
           PRINT_DEFAULT_ADMIN_PASSWORD, 
           ADMIN, 
           Account::ADMIN_ACCOUNT), 
    employeeID{++adminCount + 1000} {}

Admin::Admin(std::string userFirstName, 
    std::string userLastName, 
    std::string userID, 
    std::string userPassword)
    : User(userFirstName, 
        userLastName, 
        userID, 
        userPassword, 
        ADMIN, 
        Account::ADMIN_ACCOUNT){}

void Admin::showMenu() const {
    std::cout <<  PRINT_ADMIN_MENU << std::endl;
}
