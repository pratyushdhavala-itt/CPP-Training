#include <iostream>
#include <ctime>

#include "date_time.h"
#include "constants.h"

DateTime::DateTime() {

    std::time_t timeNow = std::time(nullptr);
    std::tm* localTime = std::localtime(&timeNow);

    day = localTime->tm_mday;
    month = localTime->tm_mon + 1;
    year = localTime->tm_year + 1900;
    hour = localTime->tm_hour;
    minute = localTime->tm_min;
    second = localTime->tm_sec;
}

std::string DateTime::toString() {
    
    return std::to_string(day) + PRINT_SLASH +
           std::to_string(month) + PRINT_SLASH +
           std::to_string(year) + PRINT_SPACE +
           std::to_string(hour) + PRINT_COLON +
           std::to_string(minute) + PRINT_COLON +
           std::to_string(second);
}
