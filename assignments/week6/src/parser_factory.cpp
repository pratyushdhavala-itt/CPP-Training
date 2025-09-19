#include <iostream>

#include "parser_factory.h"
#include "parser.h"
#include "json_parser.h"
#include "csv_parser.h"
#include "xml_parser.h"
#include "constants.h"
#include "parser_exception.h"

Parser::FileFormat ParserFactory::detectFileFormat(const std::string& filePath) {
    Parser::FileFormat fileFormat;
    int extensionIndex = filePath.find_last_of('.');
    if (extensionIndex == std::string::npos) {
        return Parser::UNKNOWN;
    }
    std::string extension = filePath.substr(extensionIndex + 1);
    for (char& currentChar : extension) {
        currentChar = std::tolower(currentChar);
    }
    if (extension == PRINT_JSON_EXTENSION) {
        fileFormat = Parser::JSON;
    } else if (extension == PRINT_XML_EXTENSION) {
        fileFormat = Parser::XML;
    } else if (extension == PRINT_CSV_EXTENSION) {
        fileFormat = Parser::CSV;
    } else {
        fileFormat = Parser::UNKNOWN;
    }
    return fileFormat;
}

Parser* ParserFactory::getParser(const std::string& filePath) {
    
    Parser::FileFormat fileFormat;  
    Parser* parser = nullptr;

    fileFormat = detectFileFormat(filePath);

    switch(fileFormat) {
        case Parser::JSON:
            parser = new JSONParser();
            break;

        case Parser::XML:
            parser = new XMLParser();
            break;

        case Parser::CSV:
            parser = new CSVParser();
            break;

        default:
            throw ParseException("Unsupported or unknown file format: " + filePath); 
    }
    return parser;
}