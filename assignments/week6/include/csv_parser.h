#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include "csv.hpp"
#include "parser.h"

class CSVParser : public Parser {

public:
    void parse(const std::string& content) override;
};

#endif