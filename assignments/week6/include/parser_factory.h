#ifndef PARSER_FACTORY_H
#define PARSER_FACTORY_H

#include "parser.h"

class ParserFactory {

private:


public:
    static Parser::FileFormat detectFileFormat(const std::string& filePath);
    static Parser* getParser(const std::string& filePath);

};

#endif