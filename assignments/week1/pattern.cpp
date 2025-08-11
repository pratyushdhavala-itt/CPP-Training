#include <iostream>

void pattern(char str[]);
bool isNan(char num[]);
int charArraySize(char num[]);
void takeInput(char num[]);
double pow(double base, double exponent);
int charToNum(char num[]);

int main() {

    std::cout << "Please enter a number: " << std::endl;
    char num[10];
    std:: cin.getline(num, 9);

    // checks for wrong input and asks for another input
    while(isNan(num)) {
        takeInput(num);
    }

    // pattern logic function
    pattern(num);
    
}

// function to take input in case of wrong input
void takeInput(char num[]) {
    std::cout << "Wrong input! Please enter only a number: " << std::endl;
    std:: cin.getline(num, 9);
}

// function to check if any character is not a number
bool isNan(char num[]) {
    
    int length = charArraySize(num);

    int i = 0;

    while (i < length) {
        int n = num[i] - '0';
        if (n < 0 || n > 9) {
            return true;
        }
        i++;
    }
    return false;
}

// function to calculate the size of the char array
int charArraySize(char num[]) {

    int size = 0;

    while (num[size] != '\0') {
        size++;
    }

    return size;
}

// function to convert char to num
int charToNum(char num[]) {

    int length = charArraySize(num);
    int result = 0;

    for (int i = 0; i < length; i++) {
        int n = num[i] - '0';
        n = n * pow(10, length - i - 1);
        result += n;
    }
    return result;
}

// function to calculate exponents
double pow(double base, double exponent) {

    double result = 1.0;

    if (exponent >= 0) {

        for (int i = 0; i < exponent; i++) {
            result *= base;
        }
    }

    return result;
}

// function to create the pattern, contains the pattern logic
void pattern(char str[]) {

    int num = charToNum(str);

    int k = 0;

    for (int i = 0; i < num; i++) {

        if (num % 2 != 0 && i <= num / 2) {
            k++;
        } else if (num % 2 == 0 && i < num / 2) {
            k++;
        } else {
            k--;
        }
        
        for (int j = 0; j < num; j++) {

            if (j >= k && j < num - k) {
                std::cout << "  ";
                continue;
            }

            if (j <= num / 2) {
                if (j % 2 == 0) {
                    std::cout << "1 ";
                } else {
                    std::cout << "0 ";
                }
            } else {
                if (i % 2 == 0 && j % 2 == 0) {
                    std::cout << "1 ";
                } else if (i % 2 == 0 && j % 2 != 0) {
                    std::cout << "0 ";
                } else if (j % 2 == 0) {
                    std::cout << "0 ";
                } else {
                    std::cout << "1 ";
                }
            }
        }
        std::cout << "\n";
    }
}