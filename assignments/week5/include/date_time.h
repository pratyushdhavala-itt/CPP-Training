#ifndef DATE_TIME_H
#define DATE_TIME_H

class DateTime {

private:
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int second;

public:
    DateTime();
    std::string toString();
};

#endif
