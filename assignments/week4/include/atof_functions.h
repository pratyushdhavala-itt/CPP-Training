#ifndef ATOF_H
#define ATOF_H
namespace Atof {

    int convertToInteger(const char* input);

    int calculateInputLength(const char* input);

    double findPower(double base, double exponent);

    void removeWhiteSpaces(char* input);

    int findPreDecimalPointLength(const char* input);

    int findPostDecimalPointLength(const char* input);
    
    double convertToFloatingNumber(const char* input);

    int firstDecimalIndex(const char* input);

    double convertToNumber(const char* input);

};

#endif