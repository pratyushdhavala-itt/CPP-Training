#include <iostream>
#include <fstream>


void parseLine(std::string line) {


}

int main() {
    
    std::fstream file;
    file.open("log.txt", std::ios::in);

    std::string line;
    std::getline(file, line);

    parseLine(line);

}