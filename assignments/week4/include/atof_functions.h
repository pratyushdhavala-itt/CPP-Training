#ifndef ATOF_H
#define ATOF_H
class Atof {
    
public:

    static int convertToInteger(const char* input);

    static int calculateInputLength(const char* input);

    static double findPower(double base, double exponent);

    static void removeWhiteSpaces(char* input);

    static int findPreDecimalPointLength(const char* input);

    static int findPostDecimalPointLength(const char* input);
    
    static double convertToFloatingNumber(const char* input);

    static int firstDecimalIndex(const char* input);

    static double convertToNumber(const char* input);

};

#endif
