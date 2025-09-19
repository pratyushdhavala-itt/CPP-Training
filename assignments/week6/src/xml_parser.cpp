#include <iostream>
#include <fstream>
#include <pugixml.hpp>
#include <sstream>

#include "xml_parser.h"
#include "parser_exception.h"
#include "constants.h"


void XMLParser::parse(const std::string& filePath) {
    std::string fileContent = readFile(filePath);
    pugi::xml_document xmlDocument;
    pugi::xml_parse_result parseResult = xmlDocument.load_string(fileContent.c_str());

    if (!parseResult) {
        throw ParseException(PRINT_XML_PARSE_ERROR + std::string(parseResult.description()));
    }

    std::ostringstream outputString;
    xmlDocument.print(outputString, "  ");  
    parsedData = outputString.str();
}
