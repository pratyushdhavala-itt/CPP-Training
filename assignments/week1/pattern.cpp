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
    std::cout << '\n';

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
    std::cout << '\n';
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

    int printSlots = 0; // variable for how many numbers can be printed in each side (left, right)

    // outer loop for columns
    for (int col = 0; col < num; col++) {

        // if num is odd & col in first half, then increment blankSpace
        if (num % 2 != 0 && col <= num / 2) {
            printSlots++;
        } else if (num % 2 == 0 && col < num / 2) { // if num is even
            printSlots++;
        } else { // if col is in second half, then decrement blankSpace
            printSlots--;
        }
        
        // inner loop for rows
        for (int row = 0; row < num; row++) {


            // if row is greater or lesser than printSlots, then just print blank 
            if (row >= printSlots && row < num - printSlots) {
                std::cout << "  ";
                continue;
            }

            // if row is in the left side
            if (row <= num / 2) {
                if (row % 2 == 0) {
                    std::cout << "1 ";
                } else {
                    std::cout << "0 ";
                }
            } else { // if row is in the right side
                if (col % 2 == 0 && row % 2 == 0) {
                    std::cout << "1 ";
                } else if (col % 2 == 0 && row % 2 != 0) {
                    std::cout << "0 ";
                } else if (row % 2 == 0) {
                    std::cout << "0 ";
                } else {
                    std::cout << "1 ";
                }
            }
        }
        std::cout << "\n";
    }
}