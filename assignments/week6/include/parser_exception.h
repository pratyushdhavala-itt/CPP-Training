#ifndef PARSE_EXCEPTION
#define PARSE_EXCEPTION

#include <stdexcept>

class ParseException : public std::runtime_error {

public:
    explicit ParseException(const std::string& message) : std::runtime_error(message) {}

};

#endif