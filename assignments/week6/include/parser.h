#ifndef PARSER_H
#define PARSER_H

#include <iostream>

class Parser {

protected:

    std::string parsedData;

public:

    enum FileFormat {
        JSON = 1,
        XML = 2,
        CSV = 3,
        UNKNOWN = 4,
    };

    std::string readFile(const std::string& filePath) const;
    std::string getParsedData() const;

    virtual void parse(const std::string& content) = 0;

};

#endif
