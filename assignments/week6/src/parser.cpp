#include <iostream>
#include <fstream>

#include "parser.h"
#include "parser_exception.h"
#include "constants.h"

Parser::Parser(const std::string& filename) : filename{filename} {

    std::fstream file;
    file.open(filename);

    if (!file) {
        throw ParseException("Could not open file: " + filename);
    }
}

Parser::~Parser(){}