#include <iostream>

#include "csv_parser.h"
#include "csv.hpp"
#include "parser_exception.h"
#include "constants.h"

void CSVParser::parse(const std::string& filePath) {
    try {
        csv::CSVReader fileReader(filePath);

        parsedData.clear();

        for (csv::CSVRow& csvRow : fileReader) {
            for (csv::CSVField& csvField : csvRow) {
                parsedData += csvField.get<std::string>() + " ";
            }
            parsedData += "\n";
        }

    } catch (const std::exception& e) {
        throw ParseException(PRINT_CSV_PARSE_ERROR + std::string(e.what()));
    }
}
