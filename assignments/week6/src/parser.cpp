#include <iostream>
#include <fstream>

#include "parser.h"
#include "parser_exception.h"
#include "constants.h"

std::string Parser::readFile(const std::string& filePath) const {

    std::ifstream file(filePath);
    if (!file) {
        throw ParseException(PRINT_FILE_ERROR + filePath);
    }

    std::string fileContent;
    std::string currentLine;

    while (std::getline(file, currentLine)) {
        fileContent += currentLine + PRINT_NEXT_LINE; 
    }
    return fileContent;
}

std::string Parser::getParsedData() const {
    return parsedData;
}
