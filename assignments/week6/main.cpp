#include <iostream>

#include "parser.h"
#include "parser_factory.h"
#include "parser_exception.h"
#include "constants.h"

int main() {

    while (true) {
        std::string filePath;
        std::cout << PRINT_ENTER_FILE;
        std::getline(std::cin, filePath);

        Parser* parser = nullptr;
        try {
            parser = ParserFactory::getParser(filePath);

            parser->parse(filePath);

            std::cout << parser->getParsedData() << std::endl;
        } catch(const ParseException& p) {
            std::cout << PRINT_ERROR << p.what() << std::endl;
        }
    }
}