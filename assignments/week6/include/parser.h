#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>

class Parser {

protected:

    std::string filename;

public:

    enum FileFormat {
        JSON = 1,
        XML = 2,
        CSV = 3,
        UNKNOWN = 4,
    };

    Parser(const std::string& filename);
    virtual void parse() = 0;
    virtual std::string getParsedData() = 0;
    FileFormat fileFormat;
    virtual ~Parser();
};

#endif
