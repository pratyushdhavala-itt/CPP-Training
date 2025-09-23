#include<iostream>
#include <fstream>
#include "csv.hpp"

#include "csv_parser.h"
#include "person.h"
#include "constants.h"
#include "parser_exception.h"

using namespace csv;

CSVParser::CSVParser(const std::string& filename) try : Parser(filename), fileReader(filename, csv::CSVFormat().variable_columns(csv::VariableColumnPolicy::THROW)), personCount{0}, persons{nullptr} {

    for (auto& row : csv::CSVReader(filename)) {
        personCount++;
    }
    persons = new Person[personCount];
    
} catch (const std::runtime_error& r) {
    throw ParseException(r.what());
}

void CSVParser::parse() {

    int personIndex = 0;
    for (csv::CSVRow& row : fileReader) {
        if (row.size() != fileReader.get_col_names().size()) {
            throw ParseException(PRINT_CSV_EXCEPTION + std::to_string(personIndex + 1));
        }
        persons[personIndex].id = row[CSV::ID].get<int>();
        persons[personIndex].name = row[CSV::NAME].get<std::string>();
        persons[personIndex].age = row[CSV::AGE].get<int>();
        persons[personIndex].city = row[CSV::CITY].get<std::string>();
        persons[personIndex].department = row[CSV::DEPARTMENT].get<>();
        personIndex++;
    }
}


std::string CSVParser::print(const Person& p) {
    return std::to_string(p.id) + CSV::PRINT_ONE + p.name +
           CSV::PRINT_TWO + std::to_string(p.age) + CSV::PRINT_THREE +
           p.city + CSV::PRINT_FOUR + p.department + PRINT_NEXT_LINE;
}

std::string CSVParser::getParsedData() {
    std::string result;
    for (int i = 0; i < personCount; i++) {
        result += print(persons[i]);
    }
    return result;
}


std::string CSVParser::getById(int id) {
    for (int i = 0; i < personCount; i++) {
        if (persons[i].id == id) {
            return print(persons[i]);
        }
    }
    return CSV::PRINT_NO_ID_FOUND + std::to_string(id) + PRINT_NEXT_LINE;
}


std::string CSVParser::getByCity(const std::string& city) {
    std::string result;
    for (int i = 0; i < personCount; i++) {
        if (persons[i].city == city) {
            result += print(persons[i]);
        }
    }
    if (result.empty()) {
        result = CSV::PRINT_NO_PERSON_FOUND + city + PRINT_NEXT_LINE;
    }
    return result;
}

std::string CSVParser::getByDepartment(const std::string& dept) {
    std::string result;
    for (int i = 0; i < personCount; i++) {
        if (persons[i].department == dept) {
            result += print(persons[i]);
        }
    }
    if (result.empty()) {
        result = CSV::PRINT_NO_DEPARTMENT_FOUND + dept + PRINT_NEXT_LINE;
    }
    return result;
}

CSVParser::~CSVParser() {
    if (persons) {
        delete[] persons;
    }
}
