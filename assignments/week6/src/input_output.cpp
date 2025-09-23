#include <iostream>
#include "input_output.h"
#include "json_parser.h"
#include "csv_parser.h"
#include "xml_parser.h"
#include "constants.h"

int getValidOption(int minOption, int maxOption) {
    int option;
    while (true) {
        std::cin >> option;

        if (std::cin.fail() || option < minOption || option > maxOption) {
            std::cout << PRINT_INVALID_OPTION;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        } else {
            return option;
        }
    }
    std::cin.ignore(1000, '\n');
}

double getValidDouble() {
    double value;
    while (true) {
        std::cin >> value;
        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a valid number.\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        } else {
            return value;
        }
    }
    std::cin.ignore(1000, '\n');
}

void performOperations(Parser* parser) {
    Parser::FileFormat fileFormat = parser->fileFormat;
    switch (fileFormat) {
        case Parser::JSON: {
            JSONParser* jsonParser = dynamic_cast<JSONParser*>(parser);
            perfromJsonOperations(jsonParser);
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

void perfromJsonOperations(JSONParser* jsonParser) {
    std::cout << PRINT_CHOOSE_JSON_OPERATION;
    int option = 0;
    option = getValidOption(1, 2);
    if (option == 1) {
        std::cout << "Please enter the book genre: ";
        std::string input;
        std::cin.ignore(1000, '\n');
        std::getline(std::cin, input);
        std::cout << jsonParser->getByGenre(input) << std::endl;
    } else {
        std::cout << "Please enter the rating: ";
        double input = getValidDouble();
        std::cout << jsonParser->ratingFilter(input) << std::endl;
    }
}

void performXmlOperations(XMLParser* xmlParser) {

    int option = 0;
    std::cout << PRINT_CHOOSE_XML_OPERATION;
    option = getValidOption(1, 3);
    std::string input;
    switch(option) {
        case 1:
            std::cout << "Please enter the airline: ";
            std::cin.ignore(1000, '\n');
            std::getline(std::cin, input);
            std::cout << xmlParser->getByAirline(input) << std::endl;
            break;

        case 2:
            std::cout << "Please enter the origin: ";
            std::cin.ignore(1000, '\n');
            std::getline(std::cin, input);
            std::cout << xmlParser->getByOrigin(input) << std::endl;
            break;
        
        case 3:
            std::cout << "Please enter the destination: ";
            std::cin.ignore(1000, '\n');
            std::getline(std::cin, input);
            std::cout << xmlParser->getByDestination(input) << std::endl;
            break;
    }
}

void performCsvOperations(CSVParser* csvParser) {

    int option = 0;
    std::cout << PRINT_CHOOSE_CSV_OPERATION;
    option = getValidOption(1, 3);
    std::string input;
    switch(option) {
        case 1: {
            std::cout << "Please enter the ID: ";
            int intInput = getValidInt();
            std::cout << csvParser->getById(intInput) << std::endl;
            break;
        }
        case 2: {
            std::cout << "Please enter the city: ";
            std::cin.ignore(1000, '\n');
            std::getline(std::cin, input);
            std::cout << csvParser->getByCity(input) << std::endl;
            break;
        }
        case 3: {
            std::cout << "Please enter the department: ";
            std::cin.ignore(1000, '\n');
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
            std::cout << "Invalid input. Please enter a valid integer.\n";
            std::cin.clear(); 
            std::cin.ignore(1000, '\n'); 
        } else {
            return value;
        }
    }
}