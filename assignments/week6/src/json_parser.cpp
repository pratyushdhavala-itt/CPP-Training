#include <iostream>
#include <fstream>
#include "json.hpp"
#include "json_parser.h"
#include "parser_exception.h"
#include "constants.h"

void JSONParser::parse(const std::string& filePath) {

    std::string fileContent = readFile(filePath);

    try {
        nlohmann::json jsonObject = nlohmann::json::parse(fileContent);
        parsedData = jsonObject.dump(4);
        
    } catch (const nlohmann::json::parse_error& e) {
        throw ParseException(PRINT_JSON_PARSE_ERROR + std::string(e.what()));
    }
}