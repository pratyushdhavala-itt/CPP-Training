#include <iostream>
#include <fstream>

std::string getNumber(std::string line);
std::string getTimeStamp(std::string line);
bool parseLine(std::string line, std::string keywordOne, std::string keywordTwo);
std::string getStatus(std::string line);
bool isDigit(char character);

bool parseLine(std::string line, std::string keywordOne, std::string keywordTwo) {
    bool flag = false;
    std::string word;
    for (int index = 0; index < line.size(); index++) {
        if (line[index] == ' ') {
            if (word == keywordOne) {
                flag = true;
            }
            if (word == keywordTwo && flag) {
                return true;
            }
            word.clear();
        } else {
            word += line[index];
        }
    }
    return false;
}

std::string getTimeStamp(std::string line) {
    return line.substr(0, 23);
}

std::string getNumber(std::string line) {
    std::string word;
    for (char letter : line) {
        if (isDigit(letter)) {
            word += letter;
        }
    }
    return word;
}

bool isDigit(char character) {
    bool result = false;
    if (character >= '0' && character <= '9') {
        result = true;
    }
    return result;
}

std::string getStatus(std::string line) {
    std::string word;
    std::string status = "";
    for (int index = 0; index < line.size(); index++) {
        if (line[index] == ' ') {
            if (word == "status") {
                status = getNumber(line.substr(index + 1));
            }
            word.clear();
        } else {
            word += line[index];
        }
    }
    return status;
}

int main() {
    std::fstream file("demo.txt", std::ios::in);
    std::string line;
    bool exist = false;

    std::string keywordOne = "GET";
    std::string keywordTwo = "/v1/data";

    while (std::getline(file, line)) {
        exist = parseLine(line, keywordOne, keywordTwo);
        if (exist) break;
    }

    if (exist) {
        std::string timeStamp = getTimeStamp(line);
        std::string statusCode = getStatus(line);
        std::cout << "TimeStamp: " << timeStamp
                  << " Status Code: " << statusCode << std::endl;
    }
}