#include <iostream>

// forward declaration
double atofCopy(const char* str);
double pow(double base, double exponent);
int charArraySize(const char* str);
int noOfWhitespaces(const char *str);
bool startsWithAlpha(const char *str);
bool isNan(char c);

int main() {

    double result_one = atofCopy("25.5abc25.5");
    double result_two = atof("25.5abc25.5");

    std::cout << result_one << '\n';
    std::cout << result_two << '\n';
    
}

// copy of atof in built function
double atofCopy(const char* str) {

    // w = number of leading whitespaces
    int w = noOfWhitespaces(str);

    // increment the pointer by w to avoid the whitespaces
    str = str + w;

    // check if the string starts with not a number or not a decimal
    // if it does then return 0
    if (startsWithAlpha(str)) {
        return 0;
    }

    // this is the result we are going to return
    double result = 0.0;

    // length = length of the string
    int length = charArraySize(str);

    // length of the string before the decimal
    int preDecimalLength = 0;

    // length of the string after the decimal
    int postDecimalLength = 0;

    // loop to calculate the length of the string before the decimal
    for (int i = 0; i < length; i++) {

        if (str[i] != '.') {
            preDecimalLength++;
        } else {
            break;
        }
    }

    // formula for length of the string after the decimal
    postDecimalLength = length - preDecimalLength - 1;

    // boolen variable to see if we are before the decimal or after
    bool isBeforeDecimal = true;

    // boolean variable to see if the number is negative or positive
    bool isNegative = false;

    // loop for calculating the double value
    for (int i = 0; i < length; i++) {

        // if not a number is found, we stop the calculation
        if (isNan(str[i])) {
            break;
        }

        // ignoring the minus symbol
        if (str[i] == '-') {
            isNegative = true;
            continue;
        }

        // calculating the sum before the decimal point
        if (str[i] != '.' && isBeforeDecimal) {

            double num = str[i] - '0';
            num = num * pow(10, preDecimalLength - i - 1);
            result += num;
            

        } else if (str[i] == '.') { // we have reached the decimal point

            isBeforeDecimal = false;
            continue;

        } else { // calculating the sum after the decimal point

            double num = str[i] - '0';
            num = num * pow(10, -(i - preDecimalLength));
            result += num;
        }
    }

    // multiplying the result by -1 to make it negative
    if (isNegative) {
        result = result * (-1.0);
    }

    return result;
}

// function to check if character is not a decimal point or not a number
bool isNan(char c) {

    int character = c - '0';

    if (c != '.' && (character < 0 || character > 9)) {
        return true;
    }

    return false;
}

// function to check if the string starts with not a number
bool startsWithAlpha(const char *str) {

    int firstChar = str[0] - '0';

    if (str[0] != '.' && (firstChar < 0 || firstChar > 9)) {
        return true;
    }

    return false;
}

// function to calculate number of leading whitespaces
int noOfWhitespaces(const char *str) {

    int i = 0;
    while (str[i] == ' ') {
        i++;
    }

    return i;
}

// function to calculate the size of the character array
int charArraySize(const char* str) {

    int size = 0;

    while (str[size] != '\0') {

        size++;
    }

    return size;
}

// function to find the exponents
double pow(double base, double exponent) {

    double result = 1.0;

    if (exponent >= 0) {

        for (int i = 0; i < exponent; i++) {
            result *= base;
        }
    } else {

        for (int i = exponent; i < 0; i++) {
            result /= base;
        }
    }

    return result;
}