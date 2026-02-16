#ifndef OPTION_H
#define OPTION_H

#include <iostream>
#include "constants.h"
class UserOption {

private:

    char input;
    bool exitProgram;

public:

    enum Operation {
        ADDITION,
        MULTIPLICATION,
    };

    UserOption();

    bool getExitStatus();
    void print();
    Operation getOperation();

    friend std::istream& operator>>(std::istream& in, UserOption& userOption);

private:

    Operation operation;
};

#endif
