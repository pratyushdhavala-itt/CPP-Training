#ifndef XML_PARSER_H
#define XML_PARSER_H

#include "parser.h"
#include "flight.h"
class XMLParser : public Parser {

private:
    Flight* flights;
    int flightCount;

public:

    XMLParser(const std::string& filename);
    void parse() override;
    std::string getParsedData() override;
    std::string print(const Flight& f);
    std::string getByAirline(const std::string& airline);
    std::string getByOrigin(const std::string& origin);
    std::string getByDestination(const std::string& destination);
    ~XMLParser();

};

#endif