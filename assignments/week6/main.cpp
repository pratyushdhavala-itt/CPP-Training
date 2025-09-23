#include <iostream>
#include <fstream>

#include "parser.h"
#include "parser_factory.h"
#include "parser_exception.h"
#include "constants.h"
#include "input_output.h"

int main() {

    while (true) {
        std::string filename;
        std::cout << PRINT_ENTER_FILE;
        std::getline(std::cin, filename);

        Parser* parser = nullptr;
        try {
            parser = ParserFactory::getParser(RELATIVE_FILE_PATH + filename);

            parser->parse();

            parser->getParsedData();

            performOperations(parser);

        } catch(const ParseException& p) {
            std::cout << PRINT_ERROR << p.what() << std::endl;
        }
    }
}