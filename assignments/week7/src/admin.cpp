#include <iostream>
#include <string>

#include "admin.h"
#include "constants.h"

int Admin::adminCount = 1;

Admin::Admin(UserDetails adminDetails)
    : User(adminDetails, ADMIN), 
        employeeId{++adminCount + 1000}{}

void Admin::showMenu() const {
    std::cout <<  PRINT_ADMIN_MENU << std::endl;
}

long Admin::getEmployeeId() {
    return employeeId;
}
