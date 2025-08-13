#include <iostream>

double atofCopy(const char* input);
double findPower(double base, double exponent);
int calculateArrayLength(const char* str);
int noOfLeadingWhitespaces(const char *str);
bool startsWithAlphabets(const char *str);
bool isNotANumber(char c);
void trimWhitespaces(char arr[]);
int findPreDecimalLength(const char *str, int length);
int lengthAfterRemovingAlphabets(const char* str);
bool checkForNegative(const char *str);

int main() {

    while(true) {

        char input[100];
        std::cout << "Please enter the number: " << std::endl;
        std::cin.getline(input, 100);
        double result = atofCopy(input);
        std::cout << "Result: " << result << '\n';

        char continueOrNot[100];
        std::cout << "Enter (Y/y) if you want to continue, or any other key to exit!" << '\n';
        std::cin.getline(continueOrNot, 100);

        trimWhitespaces(continueOrNot);

        if (continueOrNot[0] != 'Y' && continueOrNot[0] != 'y') {
            std::cout << "Thank you for using atof() ! You have exited the program." << '\n';
            break;
        }
    }
}

double atofCopy(const char* input) {

    int leadingWhitespaces = noOfLeadingWhitespaces(input);
    input = input + leadingWhitespaces;

    if (startsWithAlphabets(input)) {
        return 0;
    }

    bool isNegative = checkForNegative(input);
    if (isNegative) {
        input += 1;
    }

    double result = 0.0;
    
    int length = lengthAfterRemovingAlphabets(input);

    int preDecimalLength = findPreDecimalLength(input, length);
    int postDecimalLength = length - preDecimalLength - 1;

    bool isBeforeDecimal = true;

    for (int i = 0; i < length; i++) {

        if (isNotANumber(input[i])) {
            break;
        }

        if (input[i] != '.' && isBeforeDecimal) {

            double num = input[i] - '0';
            num = num * findPower(10, preDecimalLength - i - 1);
            result += num;
            
        } else if (input[i] == '.') { 
            isBeforeDecimal = false;
            continue;

        } else { 

            double num = input[i] - '0';
            num = num * findPower(10, -(i - preDecimalLength));
            result += num;
        }
    }

    if (isNegative) {
        result = result * (-1.0);
    }

    return result;
}

bool checkForNegative(const char *str) {
    if (str[0] == '-') {
        return true;
    }
    return false;
}

void trimWhitespaces(char arr[]) {
    int start = 0;

    while (arr[start] == ' ' || arr[start] == '\t' || arr[start] == '\n') {
        start++;
    }

    int end = start;
    while (arr[end] != '\0') {
        end++;
    }
    end--; 

    while (end >= start && (arr[end] == ' ' || arr[end] == '\t' || arr[end] == '\n')) {
        end--;
    }

    int j = 0;
    for (int i = start; i <= end; i++) {
        arr[j++] = arr[i];
    }
    arr[j] = '\0'; 
}

int lengthAfterRemovingAlphabets(const char* str) {

    int length = calculateArrayLength(str);
    int i = 0;
    while (i < length) {
        if(isNotANumber(str[i])) {
            length = i;
            break;
        }
        i++;
    }
    return length;
}

int findPreDecimalLength(const char *str, int length) {

    int preDecimalLength = 0;
    for (int i = 0; i < length; i++) {
        if (str[i] != '.') {
            preDecimalLength++;
        } else {
            break;
        }
    }

    return preDecimalLength;
}

bool isNotANumber(char c) {

    int character = c - '0';
    if (c != '.' && c != '-' && (character < 0 || character > 9)) {
        return true;
    }
    return false;
}

bool startsWithAlphabets(const char *str) {

    int firstChar = str[0] - '0';
    if (str[0] != '.' && str[0] != '-' && (firstChar < 0 || firstChar > 9)) {
        return true;
    }
    return false;
}

int noOfLeadingWhitespaces(const char *str) {

    int i = 0;
    while (str[i] == ' ') {
        i++;
    }
    return i;
}

int calculateArrayLength(const char* str) {
    
    int size = 0;
    while (str[size] != '\0') {
        size++;
    }
    return size;
}

double findPower(double base, double exponent) {
    
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