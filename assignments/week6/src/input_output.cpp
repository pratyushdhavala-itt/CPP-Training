#include <iostream>
#include "input_output.h"
#include "json_parser.h"
#include "csv_parser.h"
#include "xml_parser.h"
#include "constants.h"

enum Constants {
    ONE = 1,
    TWO = 2,
    THREE = 3,
    INPUT_LIMIT = 1000,
};

bool exitParser() {
    std::cout << PRINT_CONTINUE_PROGRAM;
    char choice;
    std::cin >> choice;
    std::cin.ignore(INPUT_LIMIT, '\n');
    bool result = false;
    if (!(choice == 'y' || choice == 'Y')) {
        result = true;
        std::cout << PRINT_EXIT_PROGRAM << std::endl;
    }
    return result;
}

int getValidOption(int minOption, int maxOption) {
    int option;
    while (true) {
        std::cin >> option;

        if (std::cin.fail() || option < minOption || option > maxOption) {
            std::cout << PRINT_INVALID_OPTION;
            std::cin.clear();
            std::cin.ignore(INPUT_LIMIT, '\n');
        } else {
            return option;
        }
    }
    std::cin.ignore(INPUT_LIMIT, '\n');
}

double getValidDouble() {
    double value;
    while (true) {
        std::cin >> value;
        if (std::cin.fail()) {
            std::cout << PRINT_INVALID_INPUT;
            std::cin.clear();
            std::cin.ignore(INPUT_LIMIT, '\n');
        } else {
            return value;
        }
    }
    std::cin.ignore(INPUT_LIMIT, '\n');
}

void performOperations(Parser* parser) {
    Parser::FileFormat fileFormat = parser->fileFormat;
    switch (fileFormat) {
        case Parser::JSON: {
            JSONParser* jsonParser = dynamic_cast<JSONParser*>(parser);
            performJsonOperations(jsonParser);
            break;
        }
        case Parser::XML: {
            XMLParser* xmlParser = dynamic_cast<XMLParser*>(parser);
            performXmlOperations(xmlParser);
            break;
        }
        case Parser::CSV: {
            CSVParser* csvParser = dynamic_cast<CSVParser*>(parser);
            performCsvOperations(csvParser);
            break;
        }
    }
}

void performJsonOperations(JSONParser* jsonParser) {
    std::cout << PRINT_CHOOSE_JSON_OPERATION;
    int option = 0;
    option = getValidOption(ONE, TWO);
    if (option == ONE) {
        std::cout << PRINT_ENTER_BOOK_GENRE;
        std::string input;
        std::cin.ignore(INPUT_LIMIT, '\n');
        std::getline(std::cin, input);
        std::cout << jsonParser->getByGenre(input) << std::endl;
    } else if (option == TWO) {
        std::cout << PRINT_ENTER_BOOK_RATING;
        double input = getValidDouble();
        std::cout << jsonParser->ratingFilter(input) << std::endl;
    } 
}

void performXmlOperations(XMLParser* xmlParser) {

    int option = 0;
    std::cout << PRINT_CHOOSE_XML_OPERATION;
    option = getValidOption(ONE, THREE);
    std::string input;
    switch(option) {
        case ONE:
            std::cout << PRINT_ENTER_AIRLINE;
            std::cin.ignore(INPUT_LIMIT, '\n');
            std::getline(std::cin, input);
            std::cout << xmlParser->getByAirline(input) << std::endl;
            break;

        case TWO:
            std::cout << PRINT_ENTER_ORIGIN;
            std::cin.ignore(INPUT_LIMIT, '\n');
            std::getline(std::cin, input);
            std::cout << xmlParser->getByOrigin(input) << std::endl;
            break;
        
        case THREE:
            std::cout << PRINT_ENTER_DESTINATION;
            std::cin.ignore(INPUT_LIMIT, '\n');
            std::getline(std::cin, input);
            std::cout << xmlParser->getByDestination(input) << std::endl;
            break;
    }
}

void performCsvOperations(CSVParser* csvParser) {

    int option = 0;
    std::cout << PRINT_CHOOSE_CSV_OPERATION;
    option = getValidOption(ONE, THREE);
    std::string input;
    switch(option) {
        case ONE: {
            std::cout << PRINT_ENTER_ID;
            int intInput = getValidInt();
            std::cout << csvParser->getById(intInput) << std::endl;
            break;
        }
        case TWO: {
            std::cout << PRINT_ENTER_CITY;
            std::cin.ignore(INPUT_LIMIT, '\n');
            std::getline(std::cin, input);
            std::cout << csvParser->getByCity(input) << std::endl;
            break;
        }
        case THREE: {
            std::cout << PRINT_ENTER_DEPT;
            std::cin.ignore(INPUT_LIMIT, '\n');
            std::getline(std::cin, input);
            std::cout << csvParser->getByDepartment(input) << std::endl;
            break;
        }
    }
}

int getValidInt() {
    int value;
    while (true) {
        std::cin >> value;

        if (std::cin.fail()) {
            std::cout << PRINT_INVALID_INPUT;
            std::cin.clear(); 
            std::cin.ignore(INPUT_LIMIT, '\n'); 
        } else {
            return value;
        }
    }
}