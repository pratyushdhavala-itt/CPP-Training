#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <rapidxml/rapidxml.hpp>

#include "parser.h"
#include "pugixml.hpp"

class XMLParser : public Parser {

public:
    void parseNode(const pugi::xml_node& node, int level = 0);
    void parse(const std::string& content);
};

#endif