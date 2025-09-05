#ifndef OPTION_H
#define OPTION_H

class Option {

private:

    char input;
    bool exitProgram;

public:

    enum Operation {
        ADDITION,
        MULTIPLICATION,
    };

    Option();

    bool getStatus();
    void print();
    Operation getOperation();

    friend std::istream& operator>>(std::istream& in, Option& option);

private:

    Operation op;
};

#endif