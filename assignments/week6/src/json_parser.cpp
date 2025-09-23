#include <iostream>
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include "json_parser.h"
#include "constants.h"

JSONParser::JSONParser(const std::string& filename) : Parser(filename), file(filename) {}

void JSONParser::parse() {

    rapidjson::IStreamWrapper stream(file);

    rapidjson::Document jsonDocument;
    jsonDocument.ParseStream(stream);

    if (jsonDocument.HasParseError()) {
        throw std::runtime_error("Error parsing JSON file");
    }

    if (!jsonDocument.HasMember("library") || !jsonDocument["library"].IsArray()) {
        throw std::runtime_error("Invalid JSON: missing 'library' array");
    }

    const rapidjson::Value& libArray = jsonDocument["library"];
    bookCount = libArray.Size();

    books = new Book[bookCount];

    for (int bookIndex = 0; bookIndex < bookCount; bookIndex++) {
        const rapidjson::Value& b = libArray[bookIndex];

        books[bookIndex].id     = b[JSON::ID].GetInt();
        books[bookIndex].title  = b[JSON::TITLE].GetString();
        books[bookIndex].author = b[JSON::AUTHOR].GetString();
        books[bookIndex].genre  = b[JSON::GENRE].GetString();
        books[bookIndex].year   = b[JSON::YEAR].GetInt();
        books[bookIndex].rating = b[JSON::RATING].GetDouble();
    }
}

std::string JSONParser::print(const Book& book) {
    return JSON::PRINT_ONE + book.title + PRINT_NEXT_LINE
         + JSON::PRINT_TWO + book.author + PRINT_NEXT_LINE
         + JSON::PRINT_THREE + book.genre + PRINT_NEXT_LINE
         + JSON::PRINT_FOUR + std::to_string(book.year) + PRINT_NEXT_LINE
         + JSON::PRINT_FIVE + std::to_string(book.rating) + PRINT_NEXT_LINE;
}

std::string JSONParser::ratingFilter(double minRating) {
    std::string result;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].rating >= minRating) {
            result += print(books[i]) + PRINT_NEXT_LINE; 
        }
    }
    if (result.empty()) {
        return JSON::PRINT_NO_RATINGS_FOUND + std::to_string(minRating) + PRINT_NEXT_LINE;
    }
    return result;
}

std::string JSONParser::getByGenre(const std::string& genre) {
    std::string result;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].genre == genre) { 
            result += print(books[i]) + PRINT_NEXT_LINE;
        }
    }
    if (result.empty()) {
        return JSON::PRINT_NO_GENRE_FOUND + genre + PRINT_NEXT_LINE;
    }
    return result;
}


std::string JSONParser::getParsedData() {
    std::string result;
    for (int i = 0; i < bookCount; i++) {
        result += print(books[i]) + PRINT_NEXT_LINE;
    }
    return result;
}

JSONParser::~JSONParser() {
    delete[] books;
}