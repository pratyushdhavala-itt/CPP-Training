#include <iostream>

#include "parser_factory.h"
#include "parser.h"
#include "json_parser.h"
#include "csv_parser.h"
#include "xml_parser.h"
#include "constants.h"
#include "parser_exception.h"

Parser::FileFormat ParserFactory::detectFileFormat(const std::string& filename) {
    Parser::FileFormat fileFormat;
    int extensionIndex = filename.find_last_of('.');
    if (extensionIndex == std::string::npos) {
        return Parser::UNKNOWN;
    }
    std::string extension = filename.substr(extensionIndex + 1);
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

Parser* ParserFactory::getParser(const std::string& filename) {
    
    Parser::FileFormat fileFormat;  
    Parser* parser = nullptr;

    fileFormat = detectFileFormat(filename);

    try {
        switch(fileFormat) {
            case Parser::JSON:
                parser = new JSONParser(filename);
                parser->fileFormat = Parser::JSON;
                break;

            case Parser::XML:
                parser = new XMLParser(filename);
                parser->fileFormat = Parser::XML;
                break;

            case Parser::CSV:
                parser = new CSVParser(filename);
                parser->fileFormat = Parser::CSV;
                break;

            default:
                throw ParseException(PRINT_FACTORY_EXCEPTION + filename); 
        }
    } catch (const ParseException& p) {
        throw;
    } catch (const std::runtime_error& r) {
        throw ParseException(r.what());
    }
    return parser;
}