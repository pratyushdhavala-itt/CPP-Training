#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"

class Admin : public User {

public:

    enum AdminBankOperations {

        CREATE_USER = 1,
        DELETE_USER = 2,
        VIEW_ALL_CUSTOMERS = 3,
    };

private:

    static int adminCount;
    long employeeId;

public:

    Admin(UserDetails adminDetails);
    virtual long getEmployeeId();
    virtual void showMenu() const override;
    virtual ~Admin() = default;
};

#endif
