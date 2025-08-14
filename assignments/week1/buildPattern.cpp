#include <iostream>

void buildPattern(char str[]);
bool isNotANumber(char num[]);
int charArraySize(char num[]);
void takeInput();
double pow(double base, double exponent);
int charToNum(char num[]);
void printMiddleRow(int num);
bool isFirstHalf(int num, int col);
void trim(char arr[]);

int main() {

    while(true) {

        takeInput();

        char continueOrNot[100];
        std::cout << "Enter (Y/y) if you want to continue, or any other key to exit!" << '\n';
        std::cin.getline(continueOrNot, 100);

        trim(continueOrNot);

        if (continueOrNot[0] != 'Y' && continueOrNot[0] != 'y') {
            std::cout << "Thank you for making Patterns! You have exited the program." << '\n';
            break;
        }
    }
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


void takeInput() {
    char num[100];
    std::cout << "Please enter a number: " << std::endl;
    std::cin.getline(num, 100);

    trim(num);

    if (isNotANumber(num)) {
        std::cout << "Wrong input! ";
        takeInput();
    } else {
        buildPattern(num);
    }

}

bool isNotANumber(char num[]) {
    
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

int charArraySize(char num[]) {

    int size = 0;

    while (num[size] != '\0') {
        size++;
    }

    return size;
}

int charToNum(char num[]) {

    int size = charArraySize(num);
    int result = 0;

    for (int i = 0; i < size; i++) {
        int sum = num[i] - '0';
        sum = sum * pow(10, size - i - 1);
        result += sum;
    }
    return result;
}

bool isEven(int num) {
    return num % 2 == 0;
}

double pow(double base, double exponent) {

    double result = 1.0;

    if (exponent >= 0) {

        for (int i = 0; i < exponent; i++) {
            result *= base;
        }
    }

    return result;
}

bool isFirstHalf(int num, int col) {

    if (isEven(num) && col < num / 2) {
        return true;
    } else if (isEven(num) && col >= num / 2) {
        return false;
    } else if (col <= num / 2) {
        return true;
    } else if (col >= (num / 2 + 1)) {
        return false;
    }
    
    return false;
}

bool isNotMiddleRow(int col, int num) {
    if (isEven(num) && col == num / 2) {
        return false;
    } else if (col == (num / 2 + 1)) {
        return false;
    }
    return true;
}

void printEvenMiddleRow(int num) {
    int i = 0;
    while (i < num / 2) {
        if (i % 2 == 0) {
            std::cout << "1 ";
        } else {
            std::cout << "0 ";
        }
        i++;
    }

    i = 0;
    while (i < num / 2) {
        if (i % 2 == 0) {
            std::cout << "1 ";
        } else {
            std::cout << "0 ";
        }
        i++;
    }
}

void printOddMiddleRow(int num) {
    int i = 0;
    while (i < num) {
        if (i % 2 == 0) {
            std::cout << "1 ";
        } else {
            std::cout << "0 ";
        }
        i++;
    }
}

void printMiddleRow(int num) {

    if(isEven(num)) {
        printEvenMiddleRow(num);
    } else {
        printOddMiddleRow(num);
    }


}
void buildPattern(char str[]) {

    int num = charToNum(str);

    int printSlots = 0; 
    for (int col = 0; col < num; col++) {

        if (isFirstHalf(num, col)) {
            printSlots++;

        } else if (isEven(num) && col == num / 2) {

        } else if (!isEven(num) && col == (num / 2)) {

        } else { 
            printSlots--;
        }
        if (!isNotMiddleRow(printSlots, num)) {

            printMiddleRow(num);
        }
        
        bool isOne = true;
        bool isOneTwo = true;
        
        for (int row = 0; row < num; row++) {
            
            if (row >= printSlots && row < num - printSlots) {
                std::cout << "  ";
                continue;
            }

            if (isNotMiddleRow(printSlots, num) && row < num / 2 && isOne) {
                std::cout << "1 ";
                isOne = !isOne;
            } else if (isNotMiddleRow(printSlots, num) && row < num / 2) {
                std::cout << "0 ";
                isOne = !isOne;
            } else if (isNotMiddleRow(printSlots, num) && isOneTwo) {
                std::cout << "1 ";
                isOneTwo = !isOneTwo;
            } else if (isNotMiddleRow(printSlots, num)) {
                std::cout << "0 ";
                isOneTwo = !isOneTwo;
            }
        }
        std::cout << "\n";
    }
}