#include <iostream>

double atofCopy(const char* str);
double pow(double base, double exponent);
int charArraySize(const char* str);
int noOfWhitespaces(const char *str);
bool startsWithAlpha(const char *str);
bool isNan(char c);
void trim(char arr[]);
int findPreDecimalLength(const char *str, int length);
int lengthAfterRemovingAlpha(const char* str);
bool checkForNegative(const char *str);

int main() {

    while(true) {

        char str[100];
        std::cout << "Please enter the number: " << std::endl;
        std::cin.getline(str, 100);
        double result_one = atofCopy(str);
        std::cout << "Result: " << result_one << '\n';

        char continueOrNot[100];
        std::cout << "Enter (Y/y) if you want to continue, or any other key to exit!" << '\n';
        std::cin.getline(continueOrNot, 100);

        trim(continueOrNot);

        if (continueOrNot[0] != 'Y' && continueOrNot[0] != 'y') {
            std::cout << "Thank you for using atof() ! You have exited the program." << '\n';
            break;
        }
    }
}

double atofCopy(const char* str) {

    int w = noOfWhitespaces(str);
    str = str + w;

    if (startsWithAlpha(str)) {
        return 0;
    }

    bool isNegative = checkForNegative(str);
    if (isNegative) {
        str += 1;
    }

    double result = 0.0;
    
    int length = lengthAfterRemovingAlpha(str);

    int preDecimalLength = findPreDecimalLength(str, length);
    int postDecimalLength = length - preDecimalLength - 1;

    bool isBeforeDecimal = true;

    for (int i = 0; i < length; i++) {

        if (isNan(str[i])) {
            break;
        }

        if (str[i] != '.' && isBeforeDecimal) {

            double num = str[i] - '0';
            num = num * pow(10, preDecimalLength - i - 1);
            result += num;
            
        } else if (str[i] == '.') { 

            isBeforeDecimal = false;
            continue;

        } else { 

            double num = str[i] - '0';
            num = num * pow(10, -(i - preDecimalLength));
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

void trim(char arr[]) {
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

int lengthAfterRemovingAlpha(const char* str) {

    int length = charArraySize(str);
    int i = 0;
    while (i < length) {
        if(isNan(str[i])) {
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
}

bool isNan(char c) {

    int character = c - '0';
    if (c != '.' && c != '-' && (character < 0 || character > 9)) {
        return true;
    }
    return false;
}

bool startsWithAlpha(const char *str) {

    int firstChar = str[0] - '0';
    if (str[0] != '.' && str[0] != '-' && (firstChar < 0 || firstChar > 9)) {
        return true;
    }
    return false;
}

int noOfWhitespaces(const char *str) {

    int i = 0;
    while (str[i] == ' ') {
        i++;
    }
    return i;
}

int charArraySize(const char* str) {
    
    int size = 0;
    while (str[size] != '\0') {
        size++;
    }
    return size;
}

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