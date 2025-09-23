#include <iostream>
#include <fstream>

#include "parser.h"
#include "parser_exception.h"
#include "constants.h"

Parser::Parser(const std::string& filename) : filename{filename} {

    std::fstream file;
    file.open(filename);

    if (!file) {
        throw std::runtime_error("Could not open file: " + filename);
    }
}

Parser::~Parser(){}