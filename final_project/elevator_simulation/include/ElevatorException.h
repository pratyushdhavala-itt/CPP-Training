#ifndef ELEVATOR_EXCEPTION
#define ELEVATOR_EXCEPTION

#include <exception>
#include <string>

class ElevatorException : public std::exception {

private:

std::string message;

public:

    ElevatorException(const std::string& message) : message(message) {} 

    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif