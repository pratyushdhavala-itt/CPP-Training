#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>

struct Flight {
    std::string id;
    std::string airline;
    std::string origin;
    std::string destination;
    std::string departure;
    std::string arrival;
    std::string duration;
    std::string status;
};

#endif