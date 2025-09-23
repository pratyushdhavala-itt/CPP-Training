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

            std::cout << parser->getParsedData() << std::endl;

            performOperations(parser);

            if (exitParser()) {
                break;
            }

        } catch(const ParseException& p) {
            std::cout << PRINT_ERROR << p.what() << std::endl;
        } catch (const std::runtime_error r) {
            std::cout << r.what() << std::endl;
        } 
    }
}