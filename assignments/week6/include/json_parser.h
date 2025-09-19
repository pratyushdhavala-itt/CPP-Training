#ifndef JSON_PARSER_H
#define JSON_PARSER_H
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include "parser.h"

class JSONParser : public Parser {

public:

    void parse(const std::string& content);
};

#endif