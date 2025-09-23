#ifndef JSON_PARSER_H
#define JSON_PARSER_H
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include "parser.h"
#include "book.h"

class JSONParser : public Parser {
public:

private:
    Book* books;
    int bookCount;
    std::fstream file;
public:

    JSONParser(const std::string& filename);
    void parse();
    std::string getByGenre(const std::string& genre);
    std::string ratingFilter(double rating);
    std::string print(const Book& book);
    std::string getParsedData() override;
    ~JSONParser();
};

#endif